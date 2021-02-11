#pragma once
#include<string>
class BaseShaderComponent
{
private:
	char* _outLog;
	const std::uint32_t _outLogSize;
public:
	const std::string GetLastLog();
};

