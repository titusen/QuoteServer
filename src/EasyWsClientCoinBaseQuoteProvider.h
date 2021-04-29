/*
 * EasyWsClientCoinBaseQuoteProvider.h
 *
 *  Created on: Apr 29, 2021
 *      Author: titusen
 */

#ifndef EASYWSCLIENTCOINBASEQUOTEPROVIDER_H_
#define EASYWSCLIENTCOINBASEQUOTEPROVIDER_H_

#include <memory>
#include "QuoteProvider.h"
#include "easywsclient.hpp"
#include "EventFactory.h"
using easywsclient::WebSocket;

class EasyWsClientCoinBaseQuoteProvider: public QuoteProvider {
public:
	EasyWsClientCoinBaseQuoteProvider(std::string &&uri, EventFactory *factory);
	virtual ~EasyWsClientCoinBaseQuoteProvider();
	virtual bool connect();
	virtual void subcribe(const std::vector<std::string> &symbols);
	virtual void setHandler(SubscribtionEventHandler *handler);
private:
	static const char *subcribeTemplate;
    std::string uri;
    SubscribtionEventHandler *handler;
    EventFactory *eventFactory;
    bool connected = false;
    std::unique_ptr<WebSocket> ws;
};

#endif /* EASYWSCLIENTCOINBASEQUOTEPROVIDER_H_ */
