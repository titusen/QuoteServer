#pragma once

#include <memory>
#include <wangle/channel/Handler.h>
#include <folly/ProducerConsumerQueue.h>
#include <wangle/channel/EventBaseHandler.h>
#include <wangle/bootstrap/ServerBootstrap.h>
#include <wangle/channel/AsyncSocketHandler.h>
#include <wangle/codec/LineBasedFrameDecoder.h>
#include <wangle/codec/StringCodec.h>

#include "QuoteEngine.h"

typedef wangle::Pipeline<folly::IOBufQueue&, std::string> QueuePipeline;

class QuoteServer {
public:
	QuoteServer(int port, std::unique_ptr<QuoteEngine> &&quoteEngine);
	void start();
	void subscribe();
	void stop();
	virtual ~QuoteServer() = default;
private:
	int port;
	std::unique_ptr<QuoteEngine> quoteEngine;
	wangle::ServerBootstrap<QueuePipeline> wangleServer;
};

