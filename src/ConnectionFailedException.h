#pragma once

#include <exception>

class ConnectionFailedException: public std::exception {
public:
	const char* what() {return "Connection failed";}
};
