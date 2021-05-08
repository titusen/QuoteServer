/*
 * Trade.cpp
 *
 *  Created on: Apr 29, 2021
 *      Author: titusen
 */

#include "Trade.h"
#include "SubscriptionClientConnection.h"

Trade::~Trade() {
	// TODO Auto-generated destructor stub
}

Trade::Trade(std::string &&json, std::string &&symbol, long price, long amount) : json(json), symbol(symbol), price(price), amount(amount) {
}

const std::string& Trade::getJSON() {
	return json;
}

const std::string& Trade::getSymbol() {
	return symbol;
}
