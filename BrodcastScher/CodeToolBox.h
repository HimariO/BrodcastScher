#pragma once
#include <codecvt>
#include <string>

using namespace Platform;

namespace Tool {

	std::string  STos(String^ str);
	String^  sToS(std::string str);
	std::string GetDateString(int y, int m, int d);
}