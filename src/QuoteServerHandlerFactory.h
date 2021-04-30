/*
 * QuoteServerHandlerFactory.h
 *
 *  Created on: Apr 30, 2021
 *      Author: titusen
 */

#ifndef SRC_QUOTESERVERHANDLERFACTORY_H_
#define SRC_QUOTESERVERHANDLERFACTORY_H_

#include "QuoteAnalisys.h"

class QuoteServerHandlerFactory: virtual public QuoteAnalisysIfFactory {
public:
	QuoteServerHandlerFactory() {};
	virtual ~QuoteServerHandlerFactory() override;
	virtual QuoteAnalisysIf* getHandler(
			const ::apache::thrift::TConnectionInfo &connInfo);
	virtual void releaseHandler(QuoteAnalisysIf* /* handler */);
};

#endif /* SRC_QUOTESERVERHANDLERFACTORY_H_ */
