/*
 * EventFactory.h
 *
 *  Created on: Apr 29, 2021
 *      Author: titusen
 */

#ifndef EVENTFACTORY_H_
#define EVENTFACTORY_H_

class EventFactory {
public:
	virtual ~EventFactory();
	virtual StockEvent* createEvent(const std::string &msg) = 0;
};

#endif /* EVENTFACTORY_H_ */
