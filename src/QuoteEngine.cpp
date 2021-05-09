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
	symbolToConnections[symbol].push_back(subscriptionClientConnection);
}

void QuoteEngine::onEvent(StockEvent *e) {
	auto &v = symbolToConnections[e->getSymbol()];
	for (auto it : v) {
		it->sendStockEvent(e);
	}
}

void QuoteEngine::connect() {
	quoteProvider->setHandler(this);
	quoteProvider->connect();
}
