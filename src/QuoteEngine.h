/*
 * QuoteEngine.h
 *
 *  Created on: Apr 29, 2021
 *      Author: titusen
 */

#ifndef QUOTEENGINE_H_
#define QUOTEENGINE_H_

#include "SubscribtionEventHandler.h"
#include "SubscriptionClientConnection.h"

#include <memory>
#include <unordered_map>
#include <vector>
#include <mutex>

#include "QuoteProvider.h"

class QuoteEngine: public SubscribtionEventHandler {

public:
	QuoteEngine(std::shared_ptr<QuoteProvider> quoteProvider) : quoteProvider(quoteProvider) {
	}
	virtual ~QuoteEngine();
	virtual void onSubscriptionReceived(std::string &&symbol, std::shared_ptr<SubscriptionClientConnection> subscriptionClientConnection);
	virtual void onEvent(std::shared_ptr<StockEvent> e);
	virtual void connect();
	virtual std::string getOrderBookForSymbol(const std::string symbol);
	//virtual void onConnectionDropped(SubscriptionClientConnection *subscriptionClientConnection); ????
private:
	std::shared_ptr<QuoteProvider> quoteProvider;
	std::unordered_map<std::string, std::vector<std::shared_ptr<SubscriptionClientConnection>>> symbolToConnections;
	std::unordered_map<std::string, std::string> orderBook;
	std::mutex onlyOne;
};

#endif /* QUOTEENGINE_H_ */
