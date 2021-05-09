#include "QuoteServer.h"
#include "QuoteServerHandler.h"
#include "WangleClientConnection.h"

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

void QuoteServer::subscribe(Context *context, std::string &&symbol) {
	auto it = contextToConnection.find(context);
	std::shared_ptr<SubscriptionClientConnection> connection;
	if (it == contextToConnection.end()) {
		connection = std::shared_ptr<SubscriptionClientConnection>(new WangleClientConnection(context));
		contextToConnection.insert(std::make_pair(context, connection));
	}
	else {
		connection  = it->second;
	}

	quoteEngine->onSubscriptionReceived(std::move(symbol), connection);
}
