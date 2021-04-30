/*
 * QuoteServerHandlerFactory.cpp
 *
 *  Created on: Apr 30, 2021
 *      Author: titusen
 */

#include "QuoteServerHandlerFactory.h"
#include "QuoteServerHandler.h"

QuoteServerHandlerFactory::~QuoteServerHandlerFactory() {
	// TODO Auto-generated destructor stub
}

QuoteAnalisysIf* QuoteServerHandlerFactory::getHandler(
		const ::apache::thrift::TConnectionInfo &connInfo) {
	return new QuoteServerHandler();
}

void QuoteServerHandlerFactory::releaseHandler(QuoteAnalisysIf* handler) {
	delete handler;
}
