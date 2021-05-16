
#include <iostream>
#include <memory>
#include "EasyWsClientCoinBaseQuoteProvider.h"
#include "QuoteServer.h"
#include "SimpleStockEventFactoryImpl.h"
#include "BoostWsClient.h"
#include "root_certificates.hpp"
#include "CoinBaseQuoteProvider.h"

using namespace std;

int main() {

	// The SSL context is required, and holds certificates
	ssl::context ctx { ssl::context::sslv23 };

	ctx.set_options(boost::asio::ssl::context::default_workarounds);

	ctx.set_verify_mode(boost::asio::ssl::verify_none);

	// This holds the root certificate used for verification
	load_root_certificates(ctx);


	// Run the I/O service. The call will return when
	// the socket is closed.

	unique_ptr<EventFactory> eventFactory(new SimpleStockEventFactoryImpl());
	shared_ptr<QuoteProvider> quoteProvider(new BoostWsClient(ctx, "127.0.0.1", "4440", eventFactory.get()));
//	unique_ptr<QuoteProvider> quoteProvider(new CoinBaseQuoteProvider("wss://localhost:4440"));
	unique_ptr<QuoteEngine> quoteEngine(new QuoteEngine(quoteProvider));
	QuoteServer server(4400, move(quoteEngine));
	server.start();
//	quoteProvider->connect();
//	sleep(2);
//	const vector<string> s= {"ETH-USD"};
////	quoteProvider->subscribe(s);
//
//	while (true) {
//		quoteProvider->subscribe(s);
//		sleep(2);
//	}


	return 0;
}


