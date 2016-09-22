#pragma once
#include "pch.h"
#include "CodeToolBox.h"

namespace Tool {

	std::string  STos(String^ str) {
		std::wstring ws = str->Data();
		typedef std::codecvt_utf8<wchar_t> convert_typeX;
		std::wstring_convert<convert_typeX, wchar_t> converterX;

		return converterX.to_bytes(ws);
	}

	String^  sToS(std::string str) {
		typedef std::codecvt_utf8<wchar_t> convert_typeX;
		std::wstring_convert<convert_typeX, wchar_t> converterX;
		std::wstring ws = converterX.from_bytes(str);

		return ref new String(ws.c_str());
	}

	std::string GetDateString(int y, int m, int d)
	{
		std::string s_time = std::to_string(y);
		std::string zero = "0";

		if (m <= 10)
			s_time += zero;
		s_time += std::to_string(m);

		if (d <= 10)
			s_time += zero;
		s_time += std::to_string(d);

		return s_time;
	}

}