#pragma once
#include "pch.h"
#include "UIdataContainer.h"
#include "CodeToolBox.h"

using namespace Platform;
using namespace BrodcastScher;
using json = nlohmann::json;

DayEvent::DayEvent(Platform::String^ A, Platform::String^ B, double h, Platform::String^ color) {
	this->In = A;
	this->Out = B;
	this->itemHeight = h;
	this->Color = color;
}

//************************************************************************************************************************

unsigned int BrodcastScher::DayEventDetail::counter_color = 0;

std::string BrodcastScher::DayEventDetail::color_opts[6]{
	"#99FFFF",
	"#99FFCC",
	"#FF9999",
	"#CC99FF",
	"#FFCC99",
	"#FFFF99",
};


BrodcastScher::DayEventDetail::DayEventDetail()
{
	event_name = "";
	description = "";
	type = InputType::InputDevice;
	start = new _SYSTEMTIME();
	end = new _SYSTEMTIME();
	GetSystemTime(start);
	GetSystemTime(end);
	UIobject = ref new DayEvent("", "", 0, Tool::sToS(color_opts[counter_color++ % 6]));
}


BrodcastScher::DayEventDetail::DayEventDetail(json JSON)
{
	start = new _SYSTEMTIME();
	end = new _SYSTEMTIME();
	start->wHour = JSON["start_h"];
	start->wMinute = JSON["start_m"];
	start->wSecond = JSON["start_s"];

	end->wHour = JSON["end_h"];
	end->wMinute = JSON["end_m"];
	end->wSecond = JSON["end_s"];

	int T = JSON["inputtype"];
	switch (T) {
	case 1:
		type = InputType::InputDevice;
		input_dev_index = JSON["input_device_index"];
		output_dev_index = JSON["output_device_index"];
		break;
	case 2:
		type = InputType::PlayList;
		// unfinish;
		break;
	case 3:
		type = InputType::AudioFile;
		// unfinish;
		break;
	}

	event_name = JSON["name"].get<std::string>();
	description = JSON["description"].get<std::string>();
	repeat_type = JSON["repeat_type"];

	int height = (end->wHour * 60 + end->wMinute) - (start->wHour * 60 + start->wMinute);
	auto time_tag = std::to_string(start->wHour) + ":" + std::to_string(start->wMinute) + " ~ " + std::to_string(end->wHour) + ":" + std::to_string(end->wMinute);
	UIobject = ref new DayEvent(Tool::sToS(event_name), Tool::sToS(time_tag), height, Tool::sToS(color_opts[counter_color++%6]));
}

json BrodcastScher::DayEventDetail::toJSON()
{
	int int_type = 0;

	switch (type) {
	case InputType::InputDevice:
		int_type = 1;
		break;
	case InputType::PlayList:
		int_type = 1;
		break;
	case InputType::AudioFile:
		int_type = 2;
		break;
	}

	json empty_jsob = {
		{ "name", event_name },
		{ "description", description },
		{ "start_h", start->wHour },
		{ "start_m", start->wMinute },
		{ "start_s", start->wSecond },
		{ "end_h", end->wHour },
		{ "end_m", end->wMinute },
		{ "end_s", end->wSecond },
		{ "inputtype", int_type },
		{ "input_device_index", input_dev_index },
		{ "output_device_index", output_dev_index },
		{ "input_file", "mp3/wav file path" } ,
		{ "input_playlist", "m3u file path" } ,
		{"repeat_type", repeat_type },
	};

	return empty_jsob;
}
