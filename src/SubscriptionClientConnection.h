/*
 * SubscriptionClientConnection.h
 *
 *  Created on: Apr 29, 2021
 *      Author: titusen
 */

#ifndef SUBSCRIPTIONCLIENTCONNECTION_H_
#define SUBSCRIPTIONCLIENTCONNECTION_H_

#include "StockEvent.h"

class SubscriptionClientConnection {
public:
	virtual ~SubscriptionClientConnection() = default;

	virtual void sendStockEvent(StockEvent *e) = 0;

};

#endif /* SUBSCRIPTIONCLIENTCONNECTION_H_ */
