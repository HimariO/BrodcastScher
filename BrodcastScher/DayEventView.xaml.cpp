//
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


bool EventSort(DayEventDetail A, DayEventDetail B) {
	int A_time = A.start->wHour * 60 + A.start->wMinute;
	int B_time = B.start->wHour * 60 + B.start->wMinute;

	return A_time < B_time;
}



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
	if (EventSelected != nullptr) {
		auto listview = (ListView^)sender;
		unsigned int id = 0;
		listview->Items->IndexOf(e->ClickedItem, &id);
		
		if (listview->Name == "InputDevicesList") {
			EventSelected->input_dev_index = id;
		}
		else if (listview->Name == "OutputDevicesList") {
			EventSelected->output_dev_index = id;
		}
	}
}


void BrodcastScher::DayEventView::startTimePicker_TimeChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TimePickerValueChangedEventArgs^ e)
{

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
	auto name = box->Name;
	int value = _wtoi(box->Text->Data());

	if (name == "startTimeS") {
		if (value > 59)
			value = 59;
		else if (value < 0)
			value = 0;

		EventSelected->start->wSecond = value;
	}else if (name == "startTimeM") {
		if (value > 59)
			value = 59;
		else if (value < 0)
			value = 0;

		EventSelected->start->wMinute = value;
	}else if (name == "startTimeH") {
		if (value > 24)
			value = 24;
		else if (value < 1)
			value = 1;

		EventSelected->start->wHour = value;
	}
	EventSelected->setStartTime(EventSelected->start->wHour, EventSelected->start->wMinute, EventSelected->start->wSecond);
}


void BrodcastScher::DayEventView::endTimeSec_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	auto box = (TextBox^)sender;
	auto name = box->Name;
	int value = _wtoi(box->Text->Data());

	if (name == "endTimeS") {
		if (value > 59)
			value = 59;
		else if (value < 0)
			value = 0;

		EventSelected->end->wSecond = value;
	}
	else if (name == "endTimeM") {
		if (value > 59)
			value = 59;
		else if (value < 0)
			value = 0;

		EventSelected->end->wMinute = value;
	}
	else if (name == "endTimeH") {
		if (value > 24)
			value = 24;
		else if (value < 1)
			value = 1;

		EventSelected->end->wHour = value;
	}

	EventSelected->setEndTime(EventSelected->end->wHour, EventSelected->end->wMinute, EventSelected->end->wSecond);
}


void BrodcastScher::DayEventView::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs ^ e)
{
	TimeBoxSwitch(false);

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
}


void BrodcastScher::DayEventView::UpdateUIEventList()
{
	std::sort(EventList.begin(), EventList.end(), EventSort);
	theList->Items->Clear();

	int pre_start_time = 0;
	int pre_end_time = 0;

	for (auto data : EventList) {
		int current = data.start->wHour * 60 + data.start->wMinute;

		if (pre_end_time >= current) // section will overlap
			data.UIobject->itemH -= pre_end_time - current;
		else {
			int EmptyH = current - pre_end_time;
			theList->Items->Append(ref new DayEvent("EMPTY", "", EmptyH, "#FFF4F4F4"));
		}
		pre_end_time = data.end->wHour * 60 + data.end->wMinute;
		data.UIobject->itemH = data.UIobject->itemH < 10 ? 10 : data.UIobject->itemH;
		theList->Items->Append(data.UIobject);
	}

	if (pre_end_time < 24 * 60) {
		theList->Items->Append(ref new DayEvent("EMPTY", "", 24 * 60 - pre_end_time, "#FFF4F4F4"));
	}
}


void BrodcastScher::DayEventView::UpdateDetailView()
{
	if (EventSelected == nullptr) {
		TimeBoxSwitch(false);
		return;
	}
	else {
		TimeBoxSwitch(true);
	}
	
	textbox_eventName->Text = EventSelected->UIobject->In;

	startTimeS->Text = EventSelected->start->wSecond + "";
	startTimeM->Text = EventSelected->start->wMinute + "";
	startTimeH->Text = EventSelected->start->wHour + "";
	endTimeS->Text = EventSelected->end->wSecond + "";
	endTimeM->Text = EventSelected->end->wMinute + "";
	endTimeH->Text = EventSelected->end->wHour + "";;

	// update timepicker



	// update device list
	InputDevicesList->SelectedIndex = EventSelected->input_dev_index;
	OutputDevicesList->SelectedIndex = EventSelected->output_dev_index;

	switch (EventSelected->repeat_type) {
	case 1:
		check_EveryDay->IsChecked = true;
		check_EveryWeek->IsChecked = false;
		
		break;
	case 2:
		check_EveryDay->IsChecked = false;
		check_EveryWeek->IsChecked = true;
		
		break;
	default:
		check_EveryDay->IsChecked = false;
		check_EveryWeek->IsChecked = false;

	}

	switch (EventSelected->type) {
	case InputType::InputDevice:
		input_check_setby_fucntion = true;

		check_Deviceinput->IsChecked = true;
		check_FileInput->IsChecked = false;
		check_PlayListInput->IsChecked = false;
		textbox_FilePath->Text = "...";

		contentTag_PGM->IsEnabled = false;
		contentTag_AD->IsEnabled = false;
		break;
	case InputType::AudioFile:
		input_check_setby_fucntion = true;

		check_Deviceinput->IsChecked = false;
		check_FileInput->IsChecked = true;
		check_PlayListInput->IsChecked = false;

		contentTag_PGM->IsEnabled = true;
		contentTag_AD->IsEnabled = true;

		textbox_FilePath->Text = ref new Platform::String(EventSelected->input_file_path.c_str());
		break;
	case InputType::PlayList:
		input_check_setby_fucntion = true;

		check_Deviceinput->IsChecked = false;
		check_FileInput->IsChecked = false;
		check_PlayListInput->IsChecked = true;

		contentTag_PGM->IsEnabled = true;
		contentTag_AD->IsEnabled = true;

		textbox_FilePath->Text = ref new Platform::String(EventSelected->input_playlist_path.c_str());
	}

	switch (EventSelected->content_tag)
	{
	case ContentTag::PGM:
		contentTag_PGM->IsChecked = true;
		contentTag_AD->IsChecked = false;
		break;

	case ContentTag::AD:
		contentTag_PGM->IsChecked = false;
		contentTag_AD->IsChecked = true;
		break;
	default:
		break;
	}
}


void BrodcastScher::DayEventView::theList_ItemClick(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e)
{
	auto UIele = (DayEvent^)e->ClickedItem;
	int a = 1;

	for (size_t i = 0; i < EventList.size(); i++)
	{
		if (EventList[i].UIobject == UIele) {
			EventSelected = &EventList[i];
			UpdateDetailView();
			break;
		}
	}
	
}


void BrodcastScher::DayEventView::check_EveryDay_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// this function handle not only "check_everyDay" UI, but all there of them.
	auto Name = ((CheckBox^)sender)->Name;

	if (Name == "check_EveryDay") {
		check_EveryWeek->IsChecked = false;
		
		if(EventSelected != nullptr)
			EventSelected->repeat_type = 1;
	}
	else if (Name == "check_EveryWeek") {
		check_EveryDay->IsChecked = false;
		
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
		//copyedDetail = eOnRightTap;
		copyedDetail.clear();

		for (size_t j = 0; j < EventList.size(); j++)
		{
			for (size_t i = 0; i < theList->SelectedItems->Size; i++)
			{
				auto temp = (DayEvent^)theList->SelectedItems->GetAt(i);
				if (EventList[j].UIobject == temp) {
					copyedDetail.push_back(EventList[j]);
					theList->SelectedItems->RemoveAt(i);
					break;
				}
			}
		}
					
	}
	else if (tex == "Pase") {
		for (size_t i = 0; i < copyedDetail.size(); i++)
		{
			EventList.push_back(copyedDetail[i]);
		}
		
		UpdateUIEventList();
	}
	else if (tex == "Delete") {
		copyedDetail.clear();

		for (size_t i = 0; i < theList->SelectedItems->Size; i++)
		{
			for (size_t j = 0; j < EventList.size(); j++)
			{
				auto temp = (DayEvent^)theList->SelectedItems->GetAt(i);
				if (EventList[j].UIobject == temp) {
					EventList.erase(EventList.begin() + j);
					break;
				}
			}
		}

		theList->SelectedItems->Clear();
		UpdateUIEventList();
	}
}


void BrodcastScher::DayEventView::textbox_eventName_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	auto box = (TextBox^)sender;
	if (EventSelected != nullptr) {
		EventSelected->event_name = Tool::STos(box->Text);
		EventSelected->UIobject->In= box->Text;
	}
}


// Delete Button Click
void BrodcastScher::DayEventView::Button_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	for (auto iter = EventList.begin(); iter != EventList.end(); iter++) {
		if (&*iter == EventSelected) {
			EventList.erase(iter);
			EventSelected = nullptr;
			UpdateUIEventList();
			break;
		}
	}

}


void BrodcastScher::DayEventView::check_FileInput_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	using namespace Windows::Storage;
	auto Name = ((CheckBox^)sender)->Name;
	
	if (input_check_setby_fucntion || EventSelected == nullptr) {
		input_check_setby_fucntion = false;
		return;
	}

	if (Name == "check_FileInput") {
		check_Deviceinput->IsChecked = false;
		check_PlayListInput->IsChecked = false;
		
		InputDevicesList->IsEnabled = false;
		contentTag_PGM->IsEnabled = true;
		contentTag_AD->IsEnabled = true;

		if (EventSelected != nullptr)
			EventSelected->type = InputType::AudioFile;

		Pickers::FileOpenPicker^ file_picker = ref new Pickers::FileOpenPicker();
		file_picker->FileTypeFilter->Append(".mp3");
		file_picker->FileTypeFilter->Append(".wav");
		file_picker->FileTypeFilter->Append(".wma");

		concurrency::create_task(file_picker->PickSingleFileAsync()).then([this](StorageFile^ selected_File) {
			if (selected_File != nullptr) { // filepicker canceled.
				textbox_FilePath->Text = selected_File->Path;
				EventSelected->input_file_path = selected_File->Path->Data();
				return selected_File->Properties->GetMusicPropertiesAsync();
			}
			else {
				concurrency::cancel_current_task();
			}
		}).then([this](concurrency::task<FileProperties::MusicProperties^> _task) {
			try {
				FileProperties::MusicProperties^ m_property = _task.get();
				auto times = m_property->Duration;
			
			}
			catch (Platform::COMException^ e) {
				auto debug = e->Message;
			}
		});
		
	}
	else if (Name == "check_Deviceinput") {
		check_FileInput->IsChecked = false;
		check_PlayListInput->IsChecked = false;

		InputDevicesList->IsEnabled = true;
		contentTag_PGM->IsEnabled = false;
		contentTag_AD->IsEnabled = false;

		if (EventSelected != nullptr)
			EventSelected->type = InputType::InputDevice;
	}
	else if (Name == "check_PlayListInput") {
		check_FileInput->IsChecked = false;
		check_Deviceinput->IsChecked = false;

		InputDevicesList->IsEnabled = false;
		contentTag_PGM->IsEnabled = true;
		contentTag_AD->IsEnabled = true;

		if (EventSelected != nullptr)
			EventSelected->type = InputType::PlayList;

		Pickers::FileOpenPicker^ file_picker = ref new Pickers::FileOpenPicker();
		file_picker->FileTypeFilter->Append(".m3u");

		concurrency::create_task(file_picker->PickSingleFileAsync()).then([this](StorageFile^ selected_File) {
			if (selected_File != nullptr) {
				textbox_FilePath->Text = selected_File->Path;
				EventSelected->input_playlist_path = selected_File->Path->Data();
				//return selected_File->Properties->GetMusicPropertiesAsync();
			}
			else {
				concurrency::cancel_current_task();
			}
		});
	}
	
}


void BrodcastScher::DayEventView::Button_Click_2(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (EventSelected != nullptr) {
		int S = EventSelected->start->wHour * 60 + EventSelected->start->wMinute;
		int E = EventSelected->end->wHour * 60 + EventSelected->end->wMinute;

		EventSelected->UIobject->itemH = (E - S) > 10 ? (E - S) : 10;
	}
	UpdateUIEventList();
}


void BrodcastScher::DayEventView::contentTag_PGM_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto Name = ((CheckBox^)sender)->Name;

	if (EventSelected != nullptr) {
		if (Name == "contentTag_PGM") {
			contentTag_AD->IsChecked = false;
			EventSelected->content_tag = ContentTag::PGM;
		}
		else if (Name == "contentTag_AD") {
			contentTag_PGM->IsChecked = false;
			EventSelected->content_tag = ContentTag::AD;
		}
	}
}

void BrodcastScher::DayEventView::TimeBoxSwitch(bool b)
{
	startTimeH->IsEnabled = b;
	endTimeH->IsEnabled = b;
	startTimeM->IsEnabled = b;
	endTimeM->IsEnabled = b;
	startTimeS->IsEnabled = b;
	endTimeS->IsEnabled = b;
}
