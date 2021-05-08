#pragma once

#include <string>

class StockEvent {
public:
	virtual ~StockEvent() = default;
	virtual const std::string& getJSON() = 0;
	virtual const std::string& getSymbol() = 0;
};
