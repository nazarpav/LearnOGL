#include "Logger.h"
#include<iostream>
namespace LOG {
	void Logger::LOG(std::string message)
	{
		std::cout << message << std::endl;
	}
}
