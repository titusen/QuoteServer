/*
 * WangleClientConnection.cpp
 *
 *  Created on: May 8, 2021
 *      Author: titusen
 */

#include "WangleClientConnection.h"

void WangleClientConnection::sendStockEvent(StockEvent *e) {
	context->fireWrite(e->getJSON()).get();
}
