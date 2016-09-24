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
// 空白頁項目範本已記錄在 http://go.microsoft.com/fwlink/?LinkId=234238




bool _EventSort(DayEventDetail A, DayEventDetail B) {
	int A_time = A.start->wHour * 60 + A.start->wMinute;
	int B_time = B.start->wHour * 60 + B.start->wMinute;

	return A_time < B_time;
}




PlayerTab::PlayerTab()
{
	InitializeComponent();
	
	

	auto time_updater = concurrency::create_task([this]() {
		Windows::Globalization::Calendar c;
		

		while (true) {
			c.SetToNow();
			auto s_time = c.Hour + " : " + c.Minute + " : " + c.Second;
			auto t_stamsp = c.Hour * 3600 + c.Minute * 60 + c.Second;

			// Update UI
			Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal,
				ref new Windows::UI::Core::DispatchedHandler([this, s_time, t_stamsp]() {
				textbox_currentTime->Text = s_time;

				if (least_started_event != nullptr) {
					double end = least_started_event->end->wHour * 3600 + least_started_event->end->wMinute * 60 + least_started_event->end->wSecond;
					double start = least_started_event->start->wHour * 3600 + least_started_event->start->wMinute * 60 + least_started_event->start->wSecond;
					
					LeastEventProgress->Value = 100 * (double)t_stamsp / (end - start);
				}

			})
			);
			
			// Check for task start.
			for (auto _event : event_queue) {
				auto s_t = _event.start;
				auto time_stamp = s_t->wHour * 3600 + s_t->wMinute * 60 + s_t->wSecond;

				if (t_stamsp >= time_stamp) {
					least_started_event = &_event;

					auto rely_task = concurrency::create_task(
					[this, _event]() {
						int64 runtime = (_event.end->wHour * 3600 + _event.end->wMinute * 60 + _event.end->wSecond);
						runtime -= (_event.start->wHour * 3600 + _event.start->wMinute * 60 + _event.start->wSecond);

						AudioRely rely(_event.input_dev_index, _event.output_dev_index);
						onGoingRely.push_back(rely);

						if(auto_start)
							rely.StartStreaming();

						Sleep(runtime * 1000);
						rely.StopStreaming();

						/*auto found = std::find(onGoingRely.begin(), onGoingRely.end(), rely);
						if (found != onGoingRely.end())
							onGoingRely.erase(found);*/
						
						return true;
					});
					
					onGoingTask.push_back(rely_task);
				}
			}

			Sleep(1000);
		}
	}); // task end;
	
	

	/*concurrency::create_task(DeviceInformation::FindAllAsync(MediaDevice::GetAudioCaptureSelector())).then(
		[this ](DeviceInformationCollection^ devices) {

		for (auto d : devices) {
			input_listbox->Items->Append(d->Name);
		}
		
		return DeviceInformation::FindAllAsync(MediaDevice::GetAudioRenderSelector());
	}).then(
		[this ](concurrency::task<DeviceInformationCollection^> task) {
		auto devices = task.get();

		for (auto d : devices) {
			output_listbox->Items->Append(d->Name);
		}
	});*/
	

	
}


void BrodcastScher::PlayerTab::btn_start_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
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
					event_queue.push_back(DayEventDetail(event_));
			}
		}
	}
	catch (...) {}

	try {
		if (json_file["periodic"]["week"].find(weekday) != json_file["periodic"]["week"].end()) {
			auto day_items = json_file["periodic"]["week"][weekday];

			if (day_items.size() > 0) {
				for (auto event_ : day_items)
					event_queue.push_back(DayEventDetail(event_));
			}
		}
	}
	catch (...) {}

	std::sort(event_queue.begin(), event_queue.end(), _EventSort);
	//rely->StartStreaming();
}

void BrodcastScher::PlayerTab::InitAudioGraphSetting()
{
	rely->StopStreaming();
}


void BrodcastScher::PlayerTab::btn_deviceSet_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	//rely = new AudioRely(input_listbox->SelectedIndex, output_listbox->SelectedIndex);
}
