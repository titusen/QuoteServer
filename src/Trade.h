/*
 * Trade.h
 *
 *  Created on: Apr 29, 2021
 *      Author: titusen
 */

#ifndef TRADE_H_
#define TRADE_H_

#include <string>

#include "StockEvent.h"
#include "SubscriptionClientConnection.h"
//class SubscriptionClientConnection;

class Trade : public StockEvent {

public:
	Trade(std::string &&json, std::string &&symbol, long price, long amount);
	virtual ~Trade();
	virtual const std::string& getJSON();
	virtual const std::string& getSymbol();

	long getAmount() const {
		return amount;
	}

	long getPrice() const {
		return price;
	}

private:
	std::string json;
	std::string symbol;
	long price;
	long amount;
};

#endif /* TRADE_H_ */
