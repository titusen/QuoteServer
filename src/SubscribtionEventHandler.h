#ifndef SUBSCRIBTIONEVENTHANDLER_H_
#define SUBSCRIBTIONEVENTHANDLER_H_

#include "StockEvent.h"

#include <memory>

class SubscribtionEventHandler {
public:
	virtual ~SubscribtionEventHandler() = default;
	virtual void onEvent(std::shared_ptr<StockEvent> e) = 0;
};

#endif /* SUBSCRIBTIONEVENTHANDLER_H_ */
