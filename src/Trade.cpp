/*
 * Trade.cpp
 *
 *  Created on: Apr 29, 2021
 *      Author: titusen
 */

#include "Trade.h"

Trade::~Trade() {
	// TODO Auto-generated destructor stub
}

Trade::Trade(std::string &&symbol, long price, long amount) : symbol(symbol), price(price), amount(amount) {
}

void Trade::sendByConnection(
		SubscriptionClientConnection *subscribtionClientConnection) {

	subscribtionClientConnection->onTrade(this);
}

const std::string& Trade::getSymbol() {
	return symbol;
}
