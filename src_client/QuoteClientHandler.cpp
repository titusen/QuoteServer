/*
 * QuoteClientHandler.cpp
 *
 *  Created on: Apr 30, 2021
 *      Author: titusen
 */

#include "QuoteClientHandler.h"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

QuoteClientHandler::QuoteClientHandler(std::string &&host, int port) :
		host(host), port(port) {

}

void QuoteClientHandler::start() {
	std::shared_ptr<TTransport> socket(new TSocket(host, port));
	std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
	std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
	client.reset(new QuoteAnalisysClient(protocol));
	transport->open();

	running = true;

	threadOnTrade = std::thread([this]() {
		while (this->running) {
			TradeT t;
			this->client->getTrade(t);
			this->onTrade(t);
		}
	});
	threadOnBook = std::thread([this]() {
		while (this->running) {
			LimitOrderBookT ob;
			this->client->getLimitOrderBook(ob);
			this->onBook(ob);
		}
	});
}

void QuoteClientHandler::stop() {
	running = false;
}
