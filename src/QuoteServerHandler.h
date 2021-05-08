#pragma once

#include <wangle/channel/Handler.h>
#include <folly/ProducerConsumerQueue.h>
#include <wangle/channel/EventBaseHandler.h>
#include <wangle/channel/AsyncSocketHandler.h>
#include <wangle/codec/LineBasedFrameDecoder.h>
#include <wangle/codec/StringCodec.h>

#include <iostream>
#include <atomic>

#include "QuoteServer.h"

//class QuoteServer;

class QuoteServerHandler: public wangle::HandlerAdapter<std::string> {
public:
	QuoteServerHandler(QuoteServer *server) : server(server) {}
	void read(Context* ctx, std::string msg) override;
    void transportActive(Context *ctx) override;
    void transportInactive(Context *ctx) override;
    void readException(Context *ctx, folly::exception_wrapper e) override;
private:
    QuoteServer *server;
};

class QuoteServerHandlerFactory: public wangle::PipelineFactory<QueuePipeline> {
public:
	QuoteServerHandlerFactory(QuoteServer *server): server(server) {
    }
	QueuePipeline::Ptr newPipeline(
            std::shared_ptr<folly::AsyncTransportWrapper> sock) override {
        auto pipeline = QueuePipeline::create();
        pipeline->addBack(wangle::AsyncSocketHandler(sock));
        pipeline->addBack(wangle::EventBaseHandler());
        pipeline->addBack(wangle::LineBasedFrameDecoder(8192));
        pipeline->addBack(wangle::StringCodec());
        pipeline->addBack(QuoteServerHandler(server));
        pipeline->finalize();

        return pipeline;
    }
private:
	QuoteServer *server;

};
