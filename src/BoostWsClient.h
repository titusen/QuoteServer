/*
 * BoostWsClient.h
 *
 *  Created on: May 15, 2021
 *      Author: titusen
 */

#ifndef SRC_BOOSTWSCLIENT_H_
#define SRC_BOOSTWSCLIENT_H_

#include "QuoteProvider.h"
#include "EventFactory.h"
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/beast/core/buffers_to_string.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <thread>
#include <folly/executors/task_queue/UnboundedBlockingQueue.h>

namespace beast = boost::beast;
// from <boost/beast.hpp>
namespace http = beast::http;
// from <boost/beast/http.hpp>
namespace websocket = beast::websocket;
// from <boost/beast/websocket.hpp>
namespace net = boost::asio;
// from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;
// from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;
// from <boost/asio/ip/tcp.hpp>

//------------------------------------------------------------------------------

// Report a failure

// Sends a WebSocket message and prints the response
class BoostWsClient: public std::enable_shared_from_this<BoostWsClient>,
		public QuoteProvider {
	net::io_context ioc;
	tcp::resolver resolver_;
	websocket::stream<beast::ssl_stream<beast::tcp_stream>> ws_;
	beast::flat_buffer buffer_;
	boost::beast::multi_buffer buffer_write;
	const std::string host;
	const std::string port;
	bool connected = false;
	SubscribtionEventHandler *handler;
	std::thread runThread;
	static const char *subcribeTemplate;
	folly::UnboundedBlockingQueue<std::string> inboundQueue;
	EventFactory *eventFactory;
	bool areAnySubs = false;

public:
	// Resolver and socket require an io_context

	BoostWsClient(ssl::context &ctx, const std::string &host,
			const std::string &port, EventFactory *eventFactory) :
			resolver_(net::make_strand(ioc)), ws_(net::make_strand(ioc), ctx), host(
					host), port(port), handler(nullptr), eventFactory(
					eventFactory) {

	}
	virtual ~BoostWsClient() = default;
	virtual void setHandler(SubscribtionEventHandler *handler);
	virtual bool connect();
	virtual void subscribe(const std::vector<std::string> &symbols);

	void on_resolve(beast::error_code ec, tcp::resolver::results_type results) {
		if (ec)
			return fail(ec, "resolve");

		// Set a timeout on the operation
		beast::get_lowest_layer(ws_).expires_after(std::chrono::seconds(30));

		// Make the connection on the IP address we get from a lookup
		beast::get_lowest_layer(ws_).async_connect(results,
				beast::bind_front_handler(&BoostWsClient::on_connect,
						shared_from_this()));
	}

	void on_connect(beast::error_code ec,
			tcp::resolver::results_type::endpoint_type ep) {
		if (ec)
			return fail(ec, "connect");

		// Update the host_ string. This will provide the value of the
		// Host HTTP header during the WebSocket handshake.
		// See https://tools.ietf.org/html/rfc7230#section-5.4
		std::string host_ = host + ':' + std::to_string(ep.port());

		// Set a timeout on the operation
		beast::get_lowest_layer(ws_).expires_after(std::chrono::seconds(30));

		// Set SNI Hostname (many hosts need this to handshake successfully)
		if (!SSL_set_tlsext_host_name(ws_.next_layer().native_handle(),
				host.c_str())) {
			ec = beast::error_code(static_cast<int>(::ERR_get_error()),
					net::error::get_ssl_category());
			return fail(ec, "connect");
		}

		// Perform the SSL handshake
		ws_.next_layer().async_handshake(ssl::stream_base::client,
				beast::bind_front_handler(&BoostWsClient::on_ssl_handshake,
						shared_from_this()));
	}

	void on_ssl_handshake(beast::error_code ec) {
		if (ec)
			return fail(ec, "ssl_handshake");
		std::cout << "ssl on_handshake\n";
		// Turn off the timeout on the tcp_stream, because
		// the websocket stream has its own timeout system.
		beast::get_lowest_layer(ws_).expires_never();

		// Set suggested timeout settings for the websocket
		ws_.set_option(
				websocket::stream_base::timeout::suggested(
						beast::role_type::client));

		// Set a decorator to change the User-Agent of the handshake
		ws_.set_option(
				websocket::stream_base::decorator(
						[](websocket::request_type &req) {
							req.set(http::field::user_agent,
									std::string(BOOST_BEAST_VERSION_STRING)
											+ " websocket-client-async-ssl");
						}));

		// Perform the websocket handshake
		ws_.async_handshake(host, "/",
				beast::bind_front_handler(&BoostWsClient::on_handshake,
						shared_from_this()));

	}

	void on_handshake(beast::error_code ec) {
		if (ec)
			return fail(ec, "handshake");
		std::cout << "on_handshake\n";
//		// Send the message
		waitForSubscirbes();

		ws_.async_read(buffer_,
				beast::bind_front_handler(&BoostWsClient::on_read,
						shared_from_this()));
	}

	void on_write(beast::error_code ec, std::size_t bytes_transferred) {
		boost::ignore_unused(bytes_transferred);

		if (ec)
			return fail(ec, "write");
		std::cout << "on_write\n";

		buffer_write.consume(buffer_write.size());

		// Read a message into our buffer
//		ws_.async_read(buffer_,
//				beast::bind_front_handler(&BoostWsClient::on_read,
//						shared_from_this()));
//
//		std::cout << beast::make_printable(buffer_.data()) << std::endl;
	}

	void on_read(beast::error_code ec, std::size_t bytes_transferred) {
		boost::ignore_unused(bytes_transferred);

		if (ec)
			return fail(ec, "read");
		std::cout << "on_read\n";
		std::cout << beast::make_printable(buffer_.data()) << std::endl;

		if (handler != nullptr) {
			std::string msgReceived = beast::buffers_to_string(buffer_.data());
			std::shared_ptr<StockEvent> e(
					eventFactory->createEvent(msgReceived));
			handler->onEvent(e);
		}

		buffer_.consume(buffer_.size());

		waitForSubscirbes();

		ws_.async_read(buffer_,
				beast::bind_front_handler(&BoostWsClient::on_read,
						shared_from_this()));

		// Close the WebSocket connection
//		ws_.async_close(websocket::close_code::normal,
//				beast::bind_front_handler(&BoostWsClient::on_close,
//						shared_from_this()));
	}

	void on_close(beast::error_code ec) {
		if (ec)
			return fail(ec, "close");

		// If we get here then the connection is closed gracefully

		// The make_printable() function helps print a ConstBufferSequence
		std::cout << beast::make_printable(buffer_.data()) << std::endl;
	}

	void fail(beast::error_code ec, char const *what) {
		std::cerr << what << ": " << ec.message() << "\n";
	}

	void waitForSubscirbes() {
		if (!areAnySubs || inboundQueue.size() > 0) {
			std::cout << "Waiting for subscribers\n";
			areAnySubs = true;
			std::string sub = inboundQueue.take();
			writeToBuffer(sub);
			ws_.async_write(buffer_write.data(),
					beast::bind_front_handler(&BoostWsClient::on_write,
							shared_from_this()));
		}
	}

private:
	void writeToBuffer(const std::string &s) {
		size_t n = buffer_copy(buffer_write.prepare(s.size()),
				boost::asio::buffer(s));
		buffer_write.commit(n);
	}
};
#endif /* SRC_BOOSTWSCLIENT_H_ */
