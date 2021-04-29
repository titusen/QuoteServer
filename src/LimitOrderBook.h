/*
 * LimitOrderBook.h
 *
 *  Created on: Apr 29, 2021
 *      Author: titusen
 */

#ifndef LIMITORDERBOOK_H_
#define LIMITORDERBOOK_H_

#include "StockEvent.h"

class LimitOrderBook : public StockEvent {
public:
	virtual ~LimitOrderBook();
};

#endif /* LIMITORDERBOOK_H_ */
