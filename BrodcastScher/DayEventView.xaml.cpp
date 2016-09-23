﻿//
// DayEventView.xaml.cpp
// DayEventView 類別的實作
//

#include "pch.h"
#include "DayEventView.xaml.h"
#include "CodeToolBox.h"
#include <algorithm>

using namespace BrodcastScher;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Media::Devices;
using namespace Windows::Devices::Enumeration;
using namespace Windows::Globalization;

using json = nlohmann::json;

String^ PKEY_AudioEndpoint_Supports_EventDriven_Mode = "{1da5d803-d492-4edd-8c23-e0c0ffee7f0e} 7";
Calendar ^ _calendar;
json this_day_events;


DayEventView::DayEventView()
{
	InitializeComponent();
	//DayEventDetail temp;
	//temp.UIobject = ref new DayEvent("Empty", "0:00 ~ 6:00", 360, "#FFF4F4F4");

	//EventList.push_back(temp);
	//theList->Items->Append(temp.UIobject);
	//theList->Items->Append(ref new DayEvent("[Event] Test", "Test Event", 50, "#FF82FFF4"));
	//theList->Items->Append(ref new DayEvent("Empty", "6:50 ~ 24:00", 1440-410, "#FFF4F4F4"));

	_calendar = ref new Calendar();

	concurrency::create_task(DeviceInformation::FindAllAsync(MediaDevice::GetAudioCaptureSelector())).then(
		[this](DeviceInformationCollection^ devices) {

		for (auto d : devices) {
			InputDevicesList->Items->Append(d->Name);
		}

		return DeviceInformation::FindAllAsync(MediaDevice::GetAudioRenderSelector());
	}).then(
		[this](concurrency::task<DeviceInformationCollection^> task) {
		auto devices = task.get();

		for (auto d : devices) {
			OutputDevicesList->Items->Append(d->Name);
		}
	});
}


void BrodcastScher::DayEventView::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	json dayly_array = json::array();
	json weekly_array = json::array();
	json thisday_array = json::array();

	for (auto data : EventList) {
		switch (data.repeat_type) {
		case 0:
			thisday_array.push_back(data.toJSON());
			break;
		case 1:
			dayly_array.push_back(data.toJSON());
			break;
		case 2:
			weekly_array.push_back(data.toJSON());
		}
	}

	auto debug = thisday_array.dump();
	json_file["events"][DateString] = thisday_array;
	json_file["periodic"]["day"] = dayly_array;
	json_file["periodic"]["week"][WeekDayString] = weekly_array;
	this->Frame->GoBack();
}


void BrodcastScher::DayEventView::DevicesList_ItemClick(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e)
{
	auto listview = (ListView^)sender;
	int id = listview->SelectedIndex;

	if (listview->Name == "InputDevicesList") {
		
	}else if (listview->Name == "OutputDevicesList") {

	}
}


void BrodcastScher::DayEventView::startTimePicker_TimeChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TimePickerValueChangedEventArgs^ e)
{
	int64 selectedTimeInSeconds = e->NewTime.Duration / 10000000;
	int64 hours = selectedTimeInSeconds / 3600;
	int64 minutes = (selectedTimeInSeconds % 3600) / 60;

	if (EventSelected != nullptr) {
		EventSelected->start->wHour = hours;
		EventSelected->start->wMinute = minutes;
	}
}


void BrodcastScher::DayEventView::endTimePicker_TimeChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TimePickerValueChangedEventArgs^ e)
{
	int64 selectedTimeInSeconds = e->NewTime.Duration / 10000000;
	int64 hours = selectedTimeInSeconds / 3600;
	int64 minutes = (selectedTimeInSeconds % 3600) / 60;

	if (EventSelected != nullptr) {
		EventSelected->end->wHour = hours;
		EventSelected->end->wMinute = minutes;
	}
}


void BrodcastScher::DayEventView::EnumerateAudioDevicesAsync()
{
	
	
}


void BrodcastScher::DayEventView::startTimeSec_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	auto box = (TextBox^)sender;
	int value = _wtoi(box->Text->Data());

	if (value > 59)
		value = 59;
	else if (value < 0)
		value = 0;

	EventSelected->start->wSecond = value;
}


void BrodcastScher::DayEventView::endTimeSec_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	auto box = (TextBox^)sender;
	auto value = _wtoi(box->Text->Data());

	if (value > 59)
		value = 59;
	else if (value < 0)
		value = 0;

	EventSelected->end->wSecond = value;
}


void BrodcastScher::DayEventView::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs ^ e)
{
	DateTime para = (DateTime)e->Parameter;
	_calendar->SetDateTime(para);
	auto s_time = Tool::GetDateString(_calendar->Year, _calendar->Month, _calendar->Day);
	DateString = s_time;

	try {
		this_day_events = json_file["events"][s_time];
		auto s = this_day_events.dump();
		if (this_day_events.size() > 0) {
			for (auto data : this_day_events) {
				EventList.push_back(DayEventDetail(data));
			}
		}
	}
	catch (std::domain_error e) {
		auto debug = e.what();
	}
	catch (...) {}
	
	
	try {
		WeekDayString = Tool::STos(_calendar->DayOfWeek.ToString());
		auto weekly = json_file["periodic"]["week"][WeekDayString];
		
		if (weekly.size() > 0) {
			for (auto data : weekly) {
				EventList.push_back(DayEventDetail(data));
			}
		}
	}
	catch (std::domain_error e) {

	}
	catch (...) {}


	try {
		auto daly = json_file["periodic"]["day"];

		if (daly.size() > 0) {
			for (auto data : daly) {
				EventList.push_back(DayEventDetail(data));
			}
		}
	}
	catch (std::domain_error e) {

	}
	catch (...) {}
	

	UpdateUIEventList();

	//auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Window::Current->Content);

	//if (rootFrame->CanGoBack)
	//{
	//	// If we have pages in our in-app backstack and have opted in to showing back, do so
	//	Windows::UI::Core::SystemNavigationManager::GetForCurrentView()->AppViewBackButtonVisibility =
	//		Windows::UI::Core::AppViewBackButtonVisibility::Visible;
	//}
}


void BrodcastScher::DayEventView::UpdateUIEventList()
{
	std::sort(EventList.begin(), EventList.end(), Tool::EventSort);
	theList->Items->Clear();

	int pre_start_time = 0;
	int pre_end_time = 0;

	for (auto data : EventList) {
		int current = data.start->wHour * 60 + data.start->wMinute;

		if (pre_end_time >= current) // section will overlap
			data.UIobject->itemH -= pre_end_time - current;
		else {
			int EmptyH = current - pre_end_time;
			theList->Items->Append(ref new DayEvent("Empty", "", EmptyH, "#FFF4F4F4"));
		}
		pre_end_time = data.end->wHour * 60 + data.end->wMinute;
		theList->Items->Append(data.UIobject);
	}

	if (pre_end_time < 24 * 60) {
		theList->Items->Append(ref new DayEvent("Empty", "", 24 * 60 - pre_end_time, "#FFF4F4F4"));
	}
}


void BrodcastScher::DayEventView::UpdateDetailView()
{
	if (EventSelected == nullptr)
		return;
	
	// update timepicker
	int64 h = EventSelected->start->wHour * 3600;
	int64 m = EventSelected->start->wMinute * 60;
	
	TimeSpan tp;
	tp.Duration = (h + m) * 10000000;
	startTimePicker->Time = tp;

	h = EventSelected->end->wHour * 3600;
	m = EventSelected->end->wMinute * 60;

	tp.Duration = (h + m) * 10000000;
	endTimePicker->Time = tp;

	// update device list
	InputDevicesList->SelectedIndex = EventSelected->input_dev_index;
	OutputDevicesList->SelectedIndex = EventSelected->output_dev_index;

	switch (EventSelected->repeat_type) {
	case 1:
		check_EveryDay->IsChecked = true;
		check_EveryWeek->IsChecked = false;
		check_EveryMonth->IsChecked = false;
		break;
	case 2:
		check_EveryDay->IsChecked = false;
		check_EveryWeek->IsChecked = true;
		check_EveryMonth->IsChecked = false;
		break;
	default:
		check_EveryDay->IsChecked = false;
		check_EveryWeek->IsChecked = false;
		check_EveryMonth->IsChecked = false;
	}
}


void BrodcastScher::DayEventView::theList_ItemClick(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e)
{
	auto UIele = (DayEvent^)e->ClickedItem;
	int a = 1;
	for (auto _event : EventList) {
		if (_event.UIobject == UIele) {
			EventSelected = &_event;
			break;
		}	
	}
	
	UpdateDetailView();
}


void BrodcastScher::DayEventView::check_EveryDay_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// this function handle not only "check_everyDay" UI, but all there of them.
	auto Name = ((CheckBox^)sender)->Name;

	if (Name == "check_EveryDay") {
		check_EveryWeek->IsChecked = false;
		check_EveryMonth->IsChecked = false;
		if(EventSelected != nullptr)
			EventSelected->repeat_type = 1;
	}
	else if (Name == "check_EveryWeek") {
		check_EveryDay->IsChecked = false;
		check_EveryMonth->IsChecked = false;
		if (EventSelected != nullptr)
			EventSelected->repeat_type = 2;
	}
	else {
		check_EveryWeek->IsChecked = false;
		check_EveryDay->IsChecked = false;
		if (EventSelected != nullptr)
			EventSelected->repeat_type = 3;
	}

}


void BrodcastScher::DayEventView::btn_AddEvent_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	EventList.push_back(DayEventDetail());
	EventSelected = &EventList[EventList.size() - 1];
	UpdateDetailView();
}


// Grid Inside "theList" itemTemplate's righttapped event.
void BrodcastScher::DayEventView::Grid_RightTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::RightTappedRoutedEventArgs^ e)
{
	// Getting Original Binded Data from sender.
	auto f_element = (FrameworkElement^)sender;
	auto d_context = f_element->DataContext;
	auto actual_data = (DayEvent^)d_context;

	for (auto _event : EventList) 
		if(_event.UIobject == actual_data)
			eOnRightTap = _event;
	
	auto ContextMenu =(MenuFlyout^) this->Resources->Lookup("mContextMenu");
	ContextMenu->ShowAt(nullptr, e->GetPosition(nullptr));
}


void BrodcastScher::DayEventView::MenuFlyoutItem_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto ui = (MenuFlyoutItem^)sender;
	auto tex = ui->Text;

	if (tex == "Copy") {
		copyedDetail = eOnRightTap;
	}
	else if (tex == " Pase") {
		EventList.push_back(copyedDetail);
		UpdateUIEventList();
	}
	else if (tex == "Delete") {

	}
}
