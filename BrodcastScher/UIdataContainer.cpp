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

std::string BrodcastScher::DayEventDetail::color_opts[8]{
	"#46f58c",
	"#649ef6",
	"#FF9999",
	"#e2a658",
	"#FFCC99",
	"#FFFF99",
	"#f9e48a",
	"#696969",
};


BrodcastScher::DayEventDetail::DayEventDetail()
{
	type = InputType::InputDevice;
	start = new _SYSTEMTIME();
	end = new _SYSTEMTIME();
	GetLocalTime(start);
	GetLocalTime(end);
	event_name = "";
	UIobject = ref new DayEvent(Tool::sToS(event_name), "", 0, Tool::sToS(color_opts[counter_color++ % 6]));
	//UIobject->setParent ( this);
}


BrodcastScher::DayEventDetail::DayEventDetail(json JSON)
{
	std::string ui_color = "";

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
		ui_color = color_opts[input_dev_index % 6];
		break;
	case 3:
		type = InputType::PlayList;

		content_tag = JSON["content_tag"].get<int>() == 0 ?  ContentTag::PGM :  ContentTag::AD;
		input_playlist_path = JSON["input_playlist"].get<std::wstring>();
		ui_color = color_opts[content_tag + 6];
			break;
	case 2:
		type = InputType::AudioFile;

		content_tag = JSON["content_tag"].get<int>() == 0 ? ContentTag::PGM : ContentTag::AD;
		input_file_path = JSON["input_file"].get<std::wstring>();
		ui_color = color_opts[content_tag + 6];
		break;
	}

	output_dev_index = JSON["output_device_index"];
	event_name = JSON["name"].get<std::string>();
	description = JSON["description"].get<std::string>();
	repeat_type = JSON["repeat_type"];

	int height = (end->wHour * 60 + end->wMinute) - (start->wHour * 60 + start->wMinute);
	height = height < 10 ? 10 : height;

	auto time_tag = std::to_string(start->wHour) + ":" + std::to_string(start->wMinute) + " ~ " + std::to_string(end->wHour) + ":" + std::to_string(end->wMinute);
	
	UIobject = ref new DayEvent(Tool::sToS(event_name), Tool::sToS(time_tag), height, Tool::sToS(ui_color));
	//UIobject->setParent(this);
}

json BrodcastScher::DayEventDetail::toJSON()
{
	int int_type = 0;

	switch (type) {
	case InputType::InputDevice:
		int_type = 1;
		break;
	case InputType::PlayList:
		int_type = 3;
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
		{ "input_file", input_file_path } ,
		{ "input_playlist", input_playlist_path } ,
		{"repeat_type", repeat_type },
		{"content_tag", content_tag}
	};

	return empty_jsob;
}

void BrodcastScher::DayEventDetail::setStartTime(int h, int m, int s)
{
	start->wHour = h;
	start->wMinute = m;
	start->wSecond = s;

	int height = (end->wHour * 60 + end->wMinute) - (start->wHour * 60 + start->wMinute);
	height = height < 10 ? 10 : height;
	
	if (UIobject != nullptr) {
		UIobject->itemH = height;
		UIobject->Out = Tool::sToS(std::to_string(start->wHour) + ":" + std::to_string(start->wMinute) + " ~ " + std::to_string(end->wHour) + ":" + std::to_string(end->wMinute));
	}
}

void BrodcastScher::DayEventDetail::setEndTime(int h, int m, int s)
{
	end->wHour = h;
	end->wMinute = m;
	end->wSecond = s;

	int height = (end->wHour * 60 + end->wMinute) - (start->wHour * 60 + start->wMinute);
	height = height < 10 ? 10 : height;

	if (UIobject != nullptr) {
		UIobject->itemH = height;
		UIobject->Out = Tool::sToS(std::to_string(start->wHour) + ":" + std::to_string(start->wMinute) + " ~ " + std::to_string(end->wHour) + ":" + std::to_string(end->wMinute));
	}
}

void BrodcastScher::DayEventDetail::refreshColor()
{
	
	switch (type) {
	case InputType::InputDevice:
		UIobject->Color = Tool::sToS( color_opts[input_dev_index % 6]);
		break;
	case InputType::AudioFile:
	case InputType::PlayList:
		UIobject->Color = Tool::sToS(color_opts[content_tag + 6]);
		break;
	}
}
