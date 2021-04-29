#pragma once


#include "SubscriptionClientConnection.h"
#include <string>

class StockEvent {
public:
	virtual ~StockEvent() = default;
	virtual void sendByConnection(SubscriptionClientConnection *subscribtionClientConnection) = 0;
	virtual const std::string& getSymbol() = 0;
};
