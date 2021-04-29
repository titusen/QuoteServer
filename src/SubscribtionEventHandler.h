#ifndef SUBSCRIBTIONEVENTHANDLER_H_
#define SUBSCRIBTIONEVENTHANDLER_H_

#include "StockEvent.h"

class SubscribtionEventHandler {
public:
	virtual ~SubscribtionEventHandler() = default;
	virtual void onEvent(StockEvent *e) = 0;
};

#endif /* SUBSCRIBTIONEVENTHANDLER_H_ */
