/*
 * QuoteEngine.cpp
 *
 *  Created on: Apr 29, 2021
 *      Author: titusen
 */

#include "QuoteEngine.h"

QuoteEngine::~QuoteEngine() {
	// TODO Auto-generated destructor stub
}

void QuoteEngine::onSubscriptionReceived(
		std::string &&symbol,
		std::shared_ptr<SubscriptionClientConnection> subscriptionClientConnection) {
	std::unique_lock<std::mutex> lck (onlyOne);
	symbolToConnections[symbol].push_back(subscriptionClientConnection);
	const std::vector<std::string> v(1, std::move(symbol));
	quoteProvider->subscribe(v);
}

void QuoteEngine::onEvent(std::shared_ptr<StockEvent> e) {
	std::unique_lock<std::mutex> lck (onlyOne);
	orderBook[e->getSymbol()].append(e->getJSON() + "\n");
	auto &v = symbolToConnections[e->getSymbol()];
	for (auto it : v) {
		it->sendStockEvent(e.get());
	}
}

void QuoteEngine::connect() {
	quoteProvider->setHandler(this);
	quoteProvider->connect();
}

std::string QuoteEngine::getOrderBookForSymbol(const std::string symbol) {
	std::unique_lock<std::mutex> lck (onlyOne);
	return orderBook[symbol];
}
