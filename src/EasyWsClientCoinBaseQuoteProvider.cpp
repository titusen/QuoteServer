/*
 * EasyWsClientCoinBaseQuoteProvider.cpp
 *
 *  Created on: Apr 29, 2021
 *      Author: titusen
 */

#include "EasyWsClientCoinBaseQuoteProvider.h"
#include <thread>

//const char *subcribeTemplate = "{\"type\":\"subscribe\",\"product_ids\":[\"ETH-USD\",\"ETH-EUR\"],\"channels\":[\"level2\",\"heartbeat\",{\"name\":\"ticker\",\"product_ids\":[\"ETH-BTC\",\"ETH-USD\"]}]}";
const char * EasyWsClientCoinBaseQuoteProvider::subcribeTemplate =
		"{\"type\":\"subscribe\",\"product_ids\":[%s],\"channels\":[\"level2\",\"heartbeat\",{\"name\":\"ticker\",\"product_ids\":[%s]}]}";


EasyWsClientCoinBaseQuoteProvider::EasyWsClientCoinBaseQuoteProvider(
		std::string &&uri, EventFactory *eventFactory) :
		uri(uri), handler(nullptr), eventFactory(eventFactory) {
}

EasyWsClientCoinBaseQuoteProvider::~EasyWsClientCoinBaseQuoteProvider() {
	// TODO Auto-generated destructor stub
}

bool EasyWsClientCoinBaseQuoteProvider::connect() {
	ws.reset(WebSocket::from_url(uri));
	auto wsPtr = ws.get();
	connected = true;
	std::thread getQuotes([wsPtr, this]() {
		while (wsPtr->getReadyState() != WebSocket::CLOSED) {

			wsPtr->poll();
			wsPtr->dispatch([this](const std::string &message) {
				std::unique_ptr<StockEvent> p( this->eventFactory->createEvent(message));
//				this->handler->onEvent(p.get());
			});
		}
	});

	return connected;
}

void EasyWsClientCoinBaseQuoteProvider::subscribe(
		const std::vector<std::string> &symbols) {
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

	sprintf(msg, subcribeTemplate, symbolsInLine.c_str(),
			symbolsInLine.c_str());
	ws.get()->send(std::string(msg));
}

void EasyWsClientCoinBaseQuoteProvider::setHandler(
		SubscribtionEventHandler *handler) {
	this->handler = handler;
}
