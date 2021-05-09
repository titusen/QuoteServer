
#include <iostream>
#include <memory>
#include "EasyWsClientCoinBaseQuoteProvider.h"
#include "QuoteServer.h"
#include "SimpleStockEventFactoryImpl.h"

using namespace std;

int main() {
	unique_ptr<EventFactory> eventFactory(new SimpleStockEventFactoryImpl());
	unique_ptr<QuoteProvider> quoteProvider(new EasyWsClientCoinBaseQuoteProvider("ws://ws-feed.pro.coinbase.com", eventFactory.get()));
	unique_ptr<QuoteEngine> quoteEngine(new QuoteEngine(move(quoteProvider)));
	QuoteServer server(4400, move(quoteEngine));
	server.start();
	return 0;
}


