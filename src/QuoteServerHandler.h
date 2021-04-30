/*
 * QuoteServerHanlder.h
 *
 *  Created on: Apr 30, 2021
 *      Author: titusen
 */

#ifndef SRC_QUOTESERVERHANDLER_H_
#define SRC_QUOTESERVERHANDLER_H_

#include "QuoteAnalisys.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class QuoteServerHandler : virtual public QuoteAnalisysIf {
 public:
  QuoteServerHandler() {
    // Your initialization goes here
  }

  void subscribe(const SymbolT& symbol) {
    // Your implementation goes here
    printf("subscribe\n");
  }

  void getTrade(TradeT& _return) {
    // Your implementation goes here
    printf("getTrade\n");
  }

  void getLimitOrderBook(LimitOrderBookT& _return) {
    // Your implementation goes here
    printf("getLimitOrderBook\n");
  }

};
#endif /* SRC_QUOTESERVERHANDLER_H_ */
