/*
 * SimpleStockEventFactoryImpl.h
 *
 *  Created on: Apr 29, 2021
 *      Author: titusen
 */

#ifndef SIMPLESTOCKEVENTFACTORYIMPL_H_
#define SIMPLESTOCKEVENTFACTORYIMPL_H_

#include "EventFactory.h"
#include "Trade.h"

class SimpleStockEventFactoryImpl : public EventFactory {
public:
	virtual ~SimpleStockEventFactoryImpl() = default;
	virtual StockEvent* createEvent(const std::string &msg) {
		return new Trade(std::string(msg), "a symbol", 100, 1000);
	}
};

#endif /* SIMPLESTOCKEVENTFACTORYIMPL_H_ */
