/*
 * SubscriptionClientConnection.h
 *
 *  Created on: Apr 29, 2021
 *      Author: titusen
 */

#ifndef SUBSCRIPTIONCLIENTCONNECTION_H_
#define SUBSCRIPTIONCLIENTCONNECTION_H_

class Trade;
class LimitOrderBook;

class SubscriptionClientConnection {
public:
	virtual ~SubscriptionClientConnection();

	virtual void onTrade(Trade *trade) = 0;

	virtual void onBook(LimitOrderBook *book) = 0;
};

#endif /* SUBSCRIPTIONCLIENTCONNECTION_H_ */
