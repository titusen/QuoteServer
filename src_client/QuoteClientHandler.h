/*
 * QuoteClientHandler.h
 *
 *  Created on: Apr 30, 2021
 *      Author: titusen
 */

#ifndef SRC_QUOTECLIENTHANDLER_H_
#define SRC_QUOTECLIENTHANDLER_H_

#include <thread>
#include <memory>
#include <atomic>

#include "QuoteAnalisys.h"
#include "QuoteServer_types.h"

class QuoteClientHandler {
public:
	QuoteClientHandler(std::string &&host, int port);
	virtual ~QuoteClientHandler() = default;
	void start();
	void stop();

	void subscribe(SymbolT &symbol) {
	}
protected:

	void onTrade(TradeT &trade) {
	}

	void onBook(LimitOrderBookT &book) {
	}

private:
	std::atomic<bool> running;
	std::string host;
	int port;
	std::thread threadOnTrade, threadOnBook;
	std::unique_ptr<QuoteAnalisysClient> client;
};


#endif /* SRC_QUOTECLIENTHANDLER_H_ */
