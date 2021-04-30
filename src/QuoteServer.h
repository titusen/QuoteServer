#pragma once

#include <memory>
#include <thrift/server/TServerFramework.h>


#include "QuoteEngine.h"

using namespace ::apache::thrift::server;

class QuoteServer {
public:
	QuoteServer(int port, std::unique_ptr<QuoteEngine> &&quoteEngine);
	void start();
	void stop();
	virtual ~QuoteServer() = default;
private:
	int port;
	std::unique_ptr<QuoteEngine> quoteEngine;
	std::unique_ptr<TServerFramework> thriftServer;
};

