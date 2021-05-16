/*
 * WangleClientConnection.cpp
 *
 *  Created on: May 8, 2021
 *      Author: titusen
 */

#include "WangleClientConnection.h"
#include <iostream>

void WangleClientConnection::sendStockEvent(StockEvent *e) {
	std::cout << "wangle send\n";
	context->fireWrite(e->getJSON() + "\n").get();
}
