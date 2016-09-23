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




bool EventSort(DayEventDetail A, DayEventDetail B) {
	int A_time = A.start->wHour * 60 + A.start->wMinute;
	int B_time = B.start->wHour * 60 + B.start->wMinute;

	return A_time < B_time;
}




PlayerTab::PlayerTab()
{
	InitializeComponent();

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

	std::sort(event_queue.begin(), event_queue.end(), EventSort);
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
