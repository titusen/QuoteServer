/*
 * CoinBaseQuoteProvider.h
 *
 *  Created on: Apr 29, 2021
 *      Author: titusen
 */

#ifndef COINBASEQUOTEPROVIDER_H_
#define COINBASEQUOTEPROVIDER_H_

#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include "QuoteProvider.h"
#include <thread>

typedef websocketpp::client<websocketpp::config::asio_client> client;


class CoinBaseQuoteProvider: public QuoteProvider {
public:
	CoinBaseQuoteProvider(std::string &&uri);
	virtual ~CoinBaseQuoteProvider();
	virtual bool connect();
	virtual void subscribe(const std::vector<std::string> &symbols);
	virtual void setHandler(SubscribtionEventHandler *handler);

	SubscribtionEventHandler* getHandler() {
		return handler;
	}

	client* getWebsocketClient() {
		return &websocketClient;
	}

private:
	client websocketClient;
    std::string uri;
    SubscribtionEventHandler *handler;
    bool connected = false;
    client::connection_ptr connection;
    std::thread conThread;
};

#endif /* COINBASEQUOTEPROVIDER_H_ */
