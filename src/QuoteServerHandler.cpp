#include "QuoteServerHandler.h"

void QuoteServerHandler::transportActive(Context *ctx) {

}

void QuoteServerHandler::transportInactive(Context *ctx) {

}

void QuoteServerHandler::read(Context *ctx, std::string msg) {
	std::cout << "Server received " << msg << std::endl;
	server->subscribe(ctx, std::string(msg));
}

void QuoteServerHandler::readException(Context *ctx, folly::exception_wrapper e) {

}
