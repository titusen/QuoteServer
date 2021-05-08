/*
 * WangleClientConnection.h
 *
 *  Created on: May 8, 2021
 *      Author: titusen
 */

#ifndef SRC_WANGLECLIENTCONNECTION_H_
#define SRC_WANGLECLIENTCONNECTION_H_

#include <wangle/channel/Handler.h>

#include "SubscriptionClientConnection.h"


typedef wangle::HandlerContext<std::string, std::string> Context;

class WangleClientConnection: public SubscriptionClientConnection {
public:
	WangleClientConnection(Context *context) : context(context) {};
	virtual ~WangleClientConnection() = default;

	virtual void sendStockEvent(StockEvent *e);

private:
	Context *context;
};

#endif /* SRC_WANGLECLIENTCONNECTION_H_ */
