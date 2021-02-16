#include "Utils.h"
#include<Windows.h>
namespace utils {
	void utils::Utils::SetConsoleCursorePosition(int x, int y)
	{
		COORD p = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
	}
}
