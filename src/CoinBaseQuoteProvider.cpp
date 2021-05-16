
#include "CoinBaseQuoteProvider.h"

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

// pull out the type of messages sent by our config
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;


const char *subcribeTemplate = "{\"type\":\"subscribe\",\"product_ids\":[\"ETH-USD\",\"ETH-EUR\"],\"channels\":[\"level2\",\"heartbeat\",{\"name\":\"ticker\",\"product_ids\":[\"ETH-BTC\",\"ETH-USD\"]}]}";

void on_message(CoinBaseQuoteProvider* c, websocketpp::connection_hdl hdl, message_ptr msg);


CoinBaseQuoteProvider::CoinBaseQuoteProvider(std::string &&uri) : uri(uri), handler(nullptr) {
}


CoinBaseQuoteProvider::~CoinBaseQuoteProvider() {
	// TODO Auto-generated destructor stub
}

bool CoinBaseQuoteProvider::connect() {
    try {
        // Set logging to be pretty verbose (everything except message payloads)
        websocketClient.set_access_channels(websocketpp::log::alevel::all);
        websocketClient.clear_access_channels(websocketpp::log::alevel::frame_payload);

        // Initialize ASIO
        websocketClient.init_asio();

        // Register our message handler
        websocketClient.set_message_handler(bind(&on_message, this,::_1,::_2));

        websocketpp::lib::error_code ec;
        connection = websocketClient.get_connection(uri, ec);
        if (ec) {
            std::cout << "could not create connection because: " << ec.message() << std::endl;
            return 0;
        }

        // Note that connect here only requests a connection. No network messages are
        // exchanged until the event loop starts running in the next line.
        websocketClient.connect(connection);

        // Start the ASIO io_service run loop
        // this will cause a single connection to be made to the server. c.run()
        // will exit when this connection is closed.
        conThread = std::thread([this]{this->websocketClient.run();});

    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    }
    connected = true;
    return true;
}

void CoinBaseQuoteProvider::subscribe(const std::vector<std::string> &symbols) {
	if (!connected) {
		connect();
	}
	std::string payload(subcribeTemplate);
//	websocketpp::lib::error_code ec;


	connection->send(payload);

}

void CoinBaseQuoteProvider::setHandler(SubscribtionEventHandler *handler) {
	this->handler = handler;
}


// This message handler will be invoked once for each incoming message. It
// prints the message and then sends a copy of the message back to the server.
void on_message(CoinBaseQuoteProvider* c, websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << "on_message called with hdl: " << hdl.lock().get()
              << " and message: " << msg->get_payload()
              << std::endl;


    websocketpp::lib::error_code ec;

    std::cout << msg->get_payload() << std::endl;
    if (ec) {
        std::cout << "Echo failed because: " << ec.message() << std::endl;
    }
}

