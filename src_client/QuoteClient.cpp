#include <iostream>

#include <sstream>

#include <folly/portability/GFlags.h>

#include <folly/init/Init.h>
#include <wangle/bootstrap/ClientBootstrap.h>
#include <wangle/channel/AsyncSocketHandler.h>
#include <wangle/channel/EventBaseHandler.h>
#include <wangle/codec/LineBasedFrameDecoder.h>
#include <wangle/codec/StringCodec.h>

#include "QuoteClientHandler.h"

using namespace folly;
using namespace wangle;

using namespace std;

DEFINE_int32(port, 4400, "echo server port");
DEFINE_string(host, "::1", "echo server address");

int main(int argc, char** argv) {
    folly::Init init(&argc, &argv);

    ClientBootstrap<QuoteClientPipeline> client;
    client.group(std::make_shared<folly::IOThreadPoolExecutor>(1));
    client.pipelineFactory(std::make_shared<QuoteClientPipelineFactory>());
    auto pipeline = client.connect(SocketAddress(FLAGS_host, FLAGS_port)).get();

    pipeline->write("ETH-USD\n");

    while (true) {
    	sleep(10000);
    }
	return 0;
}


