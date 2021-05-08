#include "QuoteServer.h"
#include "QuoteServerHandler.h"

QuoteServer::QuoteServer(int port, std::unique_ptr<QuoteEngine> &&quoteEngine) :
		port(port), quoteEngine(std::move(quoteEngine)) {
}

void QuoteServer::start() {
	wangleServer.childPipeline(
			std::make_shared<QuoteServerHandlerFactory>(
					QuoteServerHandlerFactory(this)));
	wangleServer.bind(port);

	quoteEngine->connect();

	wangleServer.waitForStop();
}

void QuoteServer::stop() {
	wangleServer.stop();
}
