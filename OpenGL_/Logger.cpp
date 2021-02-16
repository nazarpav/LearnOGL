#include "Logger.h"
#include<iostream>
#include"Utils.h"
namespace LOG {
	void Logger::LOG(std::string message)
	{
		utils::Utils::SetConsoleCursorePosition(2, 2);
		std::cout << message << std::endl;
	}
}
