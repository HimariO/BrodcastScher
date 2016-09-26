//
// PlayerTab.xaml.cpp
// PlayerTab 類別的實作
//

#include "pch.h"
#include "PlayerTab.xaml.h"
#include "CodeToolBox.h"
#include <algorithm>

using namespace BrodcastScher;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

using namespace Windows::Media::Audio;
using namespace Windows::Media::Render;
using namespace Windows::Devices::Enumeration;
using namespace Windows::UI::Core;
// 空白頁項目範本已記錄在 http://go.microsoft.com/fwlink/?LinkId=234238




bool _EventSort(DayEventDetail *A, DayEventDetail *B) {
	int A_time = A->start->wHour * 60 + A->start->wMinute;
	int B_time = B->start->wHour * 60 + B->start->wMinute;

	return A_time < B_time;
}




PlayerTab::PlayerTab()
{
	InitializeComponent();
	

	concurrency::create_task(DeviceInformation::FindAllAsync(MediaDevice::GetAudioCaptureSelector())).then(
		[this ](DeviceInformationCollection^ devices) {

		for (auto d : devices) {
			DeviceList_in.push_back(d->Name);
		}
		
		return DeviceInformation::FindAllAsync(MediaDevice::GetAudioRenderSelector());
	}).then(
		[this ](concurrency::task<DeviceInformationCollection^> task) {
		auto devices = task.get();

		for (auto d : devices) {
			DeviceList_out.push_back(d->Name);
		}
	});
	

	
}


void BrodcastScher::PlayerTab::btn_start_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto_start = true;

	InitEventQueue();
	CreateUpdateTask();

	for (auto reply_router : onGoingRely) {
		reply_router->StartStreaming();
	}
	auto btn = (Button^)sender;
	btn->IsEnabled = false;
}


void BrodcastScher::PlayerTab::InitEventQueue()
{
	using namespace Windows::Globalization;
	Calendar ^_calendar = ref new Calendar();

	_calendar->SetToNow();
	auto s_time = Tool::GetDateString(_calendar->Year, _calendar->Month, _calendar->Day);
	auto weekday = Tool::STos(_calendar->DayOfWeek.ToString());

	try {
		if (json_file["events"].find(s_time) != json_file["events"].end()) {
			auto day_items = json_file["events"][s_time];

			if (day_items.size() > 0) {
				for (auto event_ : day_items)
					event_queue.push_back(new DayEventDetail(event_));
			}
		}
	}
	catch (...) {}

	try {
		if (json_file["periodic"]["week"].find(weekday) != json_file["periodic"]["week"].end()) {
			auto day_items = json_file["periodic"]["week"][weekday];

			if (day_items.size() > 0) {
				for (auto event_ : day_items)
					event_queue.push_back(new DayEventDetail(event_));
			}
		}
	}
	catch (...) {}

	std::sort(event_queue.begin(), event_queue.end(), _EventSort);

	remain_job_list->Items->Clear();
	for (auto _event : event_queue)
		remain_job_list->Items->Append(_event->UIobject);
}


concurrency::task<void> BrodcastScher::PlayerTab::CreateUpdateTask()
{
	auto _updater = concurrency::create_task([this]() {
		
		

		Windows::Globalization::Calendar c;
		c.SetToNow();
		std::string date_s = Tool::GetDateString(c.Year, c.Month, c.Day);
		
		while (true) {
			auto Now = new _SYSTEMTIME();
			GetLocalTime(Now);
			c.SetToNow();
			
			auto s_time = Now->wHour + " : " + Now->wMinute + " : " + Now->wSecond;
			auto t_stamsp = Now->wHour * 3600 + Now->wMinute * 60 + Now->wSecond;

			// Check are we enter a whole new Day
			if (Tool::GetDateString(c.Year, c.Month, c.Day) != date_s) {
				// if true, update event queue from json file.

				Dispatcher->RunAsync(CoreDispatcherPriority::Normal,
					ref new DispatchedHandler([this, s_time, t_stamsp]() {
					// this will update ListView, so need to run on UI thread;
					InitEventQueue(); 
				}));

				date_s = Tool::GetDateString(c.Year, c.Month, c.Day);
			}

				

			// Update UI
			Dispatcher->RunAsync(CoreDispatcherPriority::Normal,
				ref new DispatchedHandler([this, s_time, t_stamsp]() {
				textbox_currentTime->Text = s_time;

				if (least_started_event != nullptr) {
					double end = least_started_event->end->wHour * 3600 + least_started_event->end->wMinute * 60 + least_started_event->end->wSecond;
					double start = least_started_event->start->wHour * 3600 + least_started_event->start->wMinute * 60 + least_started_event->start->wSecond;

					LeastEventProgress->Value = 100 * (double)(t_stamsp- start )/ (end - start);
				}

			})
			);

			// Check for evnet start.
			if (!event_queue.empty())
				for (auto _event : event_queue) {
					auto s_t = _event->start;
					auto time_stamp_start = s_t->wHour * 3600 + s_t->wMinute * 60 + s_t->wSecond;
					auto e_t = _event->end;
					auto time_stamp_end = e_t->wHour * 3600 + e_t->wMinute * 60 + e_t->wSecond;

					if (t_stamsp >= time_stamp_start && t_stamsp <time_stamp_end) {
						least_started_event = _event;

						Dispatcher->RunAsync(CoreDispatcherPriority::Normal,
							ref new DispatchedHandler([this, s_time, t_stamsp]() {
							auto st = least_started_event->start;
							auto et = least_started_event->end;
							textbox_startTime->Text = st->wHour + " : " + st->wMinute + " :  " + st->wSecond;
							textbox_endTime->Text = et->wHour + " : " + et->wMinute + " :  " + et->wSecond;

							switch (least_started_event->type) {
							case InputType::AudioFile:
								textbox_inputType->Text = "File [" + ref new Platform::String(least_started_event->input_file_path.c_str()) + "]";
								break;
							case InputType::PlayList:
								textbox_inputType->Text = "PlayList [" + ref new Platform::String(least_started_event->input_playlist_path.c_str()) + "]";
								break;
							default:
								textbox_inputType->Text = DeviceList_in[least_started_event->input_dev_index];
							}

							textbox_outputType->Text = DeviceList_out[least_started_event->output_dev_index];
						}));


						auto rely_task = concurrency::create_task(
							[this, _event]() {
							auto _Now = new _SYSTEMTIME();
							GetLocalTime(_Now);
							
							int64 runtime = (_event->end->wHour * 3600 + _event->end->wMinute * 60 + _event->end->wSecond);
							runtime -= _Now->wHour * 3600 + _Now->wMinute * 60 + _Now->wSecond;
							
							AudioRely *rely = nullptr;
							switch (_event->type) {
							case InputType::InputDevice:
								rely = new AudioRely(_event->input_dev_index, _event->output_dev_index, auto_start);
								break;

							case InputType::AudioFile:
								rely = new AudioRely(_event->input_file_path, _event->output_dev_index, auto_start, false);
								break;

							case InputType::PlayList:
								rely = new AudioRely(_event->input_playlist_path, _event->output_dev_index, auto_start, true);
							}
							 
							onGoingRely.push_back(rely);

							Sleep(runtime * 1000);
							rely->StopStreaming();

							auto found = std::find(onGoingRely.begin(), onGoingRely.end(), rely);
							if (found != onGoingRely.end()) {
								delete *found;
								onGoingRely.erase(found);
							}

							if (least_started_event == _event)
								least_started_event = nullptr;
							delete _event;
							return true;
						});

						onGoingTask.push_back(rely_task);
						auto found = std::find(event_queue.begin(), event_queue.end(), _event);
						if (found != event_queue.end()) {
							event_queue.erase(found);
							break;
						}
					}
				}

			Sleep(1000);
		}
		
	}); // task end;
	
	return _updater;
}


void BrodcastScher::PlayerTab::btn_deviceSet_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto box = (Button^)sender;

	if (box->Content->ToString() == "Pause") {
		auto_start = false;
		for (auto reply_router : onGoingRely) {
			reply_router->StopStreaming();
		}

		box->Content = "Continue";
	}
	else {
		auto_start = true;
		for (auto reply_router : onGoingRely) {
			reply_router->StartStreaming();
		}

		box->Content = "Pause";
	}
}


void BrodcastScher::PlayerTab::btn_stop_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	for (auto rely : onGoingRely)
		rely->StopStreaming();

	while (onGoingRely.size() > 0) {
		delete onGoingRely[0];
		onGoingRely.erase(onGoingRely.begin());
	}
		
	
	auto_start = false;

	while (event_queue.size() > 0) {
		delete event_queue[0];
		event_queue.erase(event_queue.begin());
	}

	btn_start->IsEnabled = true;
}
