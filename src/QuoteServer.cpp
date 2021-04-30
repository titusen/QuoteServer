#include "QuoteServer.h"
#include "QuoteServerHandlerFactory.h"


#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/concurrency/ThreadManager.h>
#include <memory>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::concurrency;


QuoteServer::QuoteServer(int port, std::unique_ptr<QuoteEngine> &&quoteEngine) : port(port), quoteEngine(std::move(quoteEngine)) {
}

void QuoteServer::start() {

	  const int workerCount = 4;

	  std::shared_ptr<ThreadManager> threadManager =
	    ThreadManager::newSimpleThreadManager(workerCount);
	  threadManager->threadFactory(
	    std::make_shared<ThreadFactory>());
	  threadManager->start();

	  // This server allows "workerCount" connection at a time, and reuses threads


	   thriftServer.reset( new TThreadPoolServer(
			    std::make_shared<QuoteAnalisysProcessorFactory>(std::make_shared<QuoteServerHandlerFactory>()),
			    std::make_shared<TServerSocket>(port),
			    std::make_shared<TBufferedTransportFactory>(),
			    std::make_shared<TBinaryProtocolFactory>(),
			    threadManager));
	   thriftServer->serve();
}

void QuoteServer::stop() {
	thriftServer->stop();
}
