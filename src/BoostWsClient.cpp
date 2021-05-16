/*
 * BoostWsClient.cpp
 *
 *  Created on: May 15, 2021
 *      Author: titusen
 */

#include "BoostWsClient.h"

const char * BoostWsClient::subcribeTemplate =
		"{\"type\":\"subscribe\",\"product_ids\":[%s],\"channels\":[\"level2\",\"heartbeat\",{\"name\":\"ticker\",\"product_ids\":[%s]}]}";

void BoostWsClient::setHandler(SubscribtionEventHandler *handler) {
	this->handler = handler;
}

bool BoostWsClient::connect() {

	// Look up the domain name
	resolver_.async_resolve(host.c_str(), port.c_str(),
			beast::bind_front_handler(&BoostWsClient::on_resolve,
					shared_from_this()));

	runThread = std::thread([this](){this->ioc.run();});
	connected = true;
	return connected;
}

void BoostWsClient::subscribe(const std::vector<std::string> &symbols)  {
	if (!connected) {
		connect();
	}
	std::string symbolsInLine;
	auto it = symbols.begin();
	symbolsInLine.append("\"" + *it);
	while (++it != symbols.end()) {
		symbolsInLine.append("\",\"" + *it);
	}
	symbolsInLine.append("\"");
	char msg[4096];
	memset(msg, 0, 4096);

	sprintf(msg, subcribeTemplate, symbolsInLine.c_str(),
			symbolsInLine.c_str());

	inboundQueue.add(std::string(msg));

//	ws_.async_write(net::buffer(std::string(msg)),
//			beast::bind_front_handler(&BoostWsClient::on_write,
//					shared_from_this()));
////	ws_.
//
//	ws_.async_read(buffer_,
//			beast::bind_front_handler(&BoostWsClient::on_read,
//					shared_from_this()));
//
//	std::cout << "subcribe read "  << beast::make_printable(buffer_.data()) << std::endl;
}

