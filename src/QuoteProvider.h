#pragma once

#include <vector>
#include <string>

#include "SubscribtionEventHandler.h"

class QuoteProvider {
public:

	virtual ~QuoteProvider() = default;
	virtual bool connect() = 0;
	virtual void subcribe(const std::vector<std::string> &symbols) = 0;
	virtual void setHandler(SubscribtionEventHandler *handler) = 0;
};

