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
typedef wangle::HandlerContext<std::string, std::string> Context;

class QuoteServer {
public:
	QuoteServer(int port, std::unique_ptr<QuoteEngine> &&quoteEngine);
	void start();
	void subscribe(Context* context, std::string &&symbol);
	void stop();
	virtual ~QuoteServer() = default;
private:
	int port;
	std::unique_ptr<QuoteEngine> quoteEngine;
	wangle::ServerBootstrap<QueuePipeline> wangleServer;
	std::unordered_map<Context*, std::shared_ptr<SubscriptionClientConnection>> contextToConnection;
};

