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

#include "QuoteProvider.h"

class QuoteEngine: public SubscribtionEventHandler {

public:
	QuoteEngine(std::unique_ptr<QuoteProvider> &&quoteProvider) : quoteProvider(std::move(quoteProvider)) {
	}
	virtual ~QuoteEngine();
	virtual void onSubscriptionReceived(std::string &&symbol, std::shared_ptr<SubscriptionClientConnection> subscriptionClientConnection);
	virtual void onEvent(StockEvent *e);
	virtual void connect();
	//virtual void onConnectionDropped(SubscriptionClientConnection *subscriptionClientConnection); ????
private:
	std::unique_ptr<QuoteProvider> quoteProvider;
	std::unordered_map<std::string, std::vector<std::shared_ptr<SubscriptionClientConnection>>> symbolToConnections;
};

#endif /* QUOTEENGINE_H_ */
