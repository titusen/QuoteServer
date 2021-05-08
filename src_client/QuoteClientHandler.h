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

#include <iostream>
#include <sstream>

#include <folly/portability/GFlags.h>

#include <folly/init/Init.h>
#include <wangle/bootstrap/ClientBootstrap.h>
#include <wangle/channel/AsyncSocketHandler.h>
#include <wangle/channel/EventBaseHandler.h>
#include <wangle/codec/LineBasedFrameDecoder.h>
#include <wangle/codec/StringCodec.h>

using namespace folly;
using namespace wangle;

typedef Pipeline<folly::IOBufQueue&, std::string> QuoteClientPipeline;


class QuoteClientHandler: public HandlerAdapter<std::string> {
public:
    void read(Context*, std::string msg) override {
        std::cout << "received from queue: " << msg;
    }
    void readException(Context* ctx, exception_wrapper e) override {
        std::cout << folly::exceptionStr(e) << std::endl;
        close(ctx);
    }
    void readEOF(Context* ctx) override {
        std::cout << "EOF received :(" << std::endl;
        close(ctx);
    }

public:
	virtual ~QuoteClientHandler() = default;
	void start();
	void stop();
	void subscribe() {
	}

protected:

	void onTrade() {
	}

	void onBook() {
	}

private:
	//std::atomic<bool> running;
};

// chains the handlers together to define the response pipeline
class QuoteClientPipelineFactory: public PipelineFactory<QuoteClientPipeline> {
public:
	QuoteClientPipeline::Ptr newPipeline(std::shared_ptr<AsyncTransportWrapper> sock)
            override {
        auto pipeline = QuoteClientPipeline::create();
        pipeline->addBack(AsyncSocketHandler(sock));
        pipeline->addBack(EventBaseHandler()); // ensure we can write from any thread
        pipeline->addBack(LineBasedFrameDecoder(8192, false));
        pipeline->addBack(StringCodec());
        pipeline->addBack(QuoteClientHandler());
        pipeline->finalize();
        return pipeline;
    }
};


#endif /* SRC_QUOTECLIENTHANDLER_H_ */
