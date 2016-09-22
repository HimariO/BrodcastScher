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

DayEventView::DayEventView()
{
	InitializeComponent();
	theList->Items->Append(ref new DayEvent("Empty", "0:00 ~ 6:00", 360, "#FFF4F4F4"));
	theList->Items->Append(ref new DayEvent("[Event] A", "Some description! \n Some description! Some description! Some description! Some description! Some description!", 50, "#FF82FFF4"));
	theList->Items->Append(ref new DayEvent("[Event] B", "!@#!!", 100, "#FFFFD0C6"));
	theList->Items->Append(ref new DayEvent("Empty", "0:00 ~ 6:00", 360, "#FFF4F4F4"));
	theList->Items->Append(ref new DayEvent("Empty", "0:00 ~ 6:00", 360, "#FFF4F4F4"));
	//theList->Items->Append(ref new DayEvent("A", "B", 150));
	
	//EnumerateAudioDevicesAsync();
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

	auto j = json_file;
	
	/*SYSTEMTIME now;
	GetSystemTime(&now);

	auto  y = now.wYear;
	auto m = now.wMonth;
	auto  d = now.wDay;*/
}


void BrodcastScher::DayEventView::endTimePicker_TimeChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TimePickerValueChangedEventArgs^ e)
{

}


void BrodcastScher::DayEventView::EnumerateAudioDevicesAsync()
{
	
	// Get the string identifier of the audio renderer
	Platform::String^ AudioSelector = MediaDevice::GetAudioRenderSelector();

	// Add custom properties to the query
	auto PropertyList = ref new Vector<Platform::String^>();
	PropertyList->Append(PKEY_AudioEndpoint_Supports_EventDriven_Mode);


	// Setup the asynchronous callback
	Concurrency::task<DeviceInformationCollection^> enumOperation(DeviceInformation::FindAllAsync(AudioSelector, PropertyList));
	enumOperation.then([this](DeviceInformationCollection^ DeviceInfoCollection)
	{
		if (!(DeviceInfoCollection == nullptr) || !(DeviceInfoCollection->Size == 0))
		{
			try
			{
				// Enumerate through the devices and the custom properties
				for (unsigned int i = 0; i < DeviceInfoCollection->Size; i++)
				{
					DeviceInformation^ deviceInfo = DeviceInfoCollection->GetAt(i);
					Platform::String^ DeviceInfoString = deviceInfo->Name;

					if (deviceInfo->Properties->Size > 0)
					{
						// Pull out the custom property
						Object^ DevicePropString = deviceInfo->Properties->Lookup(PKEY_AudioEndpoint_Supports_EventDriven_Mode);

						if (nullptr != DevicePropString)
						{
							DeviceInfoString = DeviceInfoString + " Device ID[" + deviceInfo->Id + "]";
						}
					}

					this->DeviceNames.Append(DeviceInfoString);
					OutputDevicesList->Items->Append(DeviceInfoString);
				}
			}
			catch (Platform::Exception^ e)
			{
				OutputDevicesList->Items->Append("Encounter Unknow Error");
			}
		}
	});
}


void BrodcastScher::DayEventView::startTimeSec_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	
}


void BrodcastScher::DayEventView::endTimeSec_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{

}

void BrodcastScher::DayEventView::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs ^ e)
{
	DateTime para = (DateTime)e->Parameter;
	_calendar->SetDateTime(para);
	auto s_time = Tool::GetDateString(_calendar->Year, _calendar->Month, _calendar->Day);

	try {
		this_day_events = json_file["event"][s_time];
		
		if (this_day_events.size() > 0) {
			for (auto data : this_day_events) {
				EventList.push_back(DayEventDetail(data));
			}
		}
	}
	catch (std::domain_error e) {

	}
	catch (...) {}

	//auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Window::Current->Content);

	//if (rootFrame->CanGoBack)
	//{
	//	// If we have pages in our in-app backstack and have opted in to showing back, do so
	//	Windows::UI::Core::SystemNavigationManager::GetForCurrentView()->AppViewBackButtonVisibility =
	//		Windows::UI::Core::AppViewBackButtonVisibility::Visible;
	//}
}


bool EventSort(DayEventDetail A, DayEventDetail B) {
	int A_time = A.start->wHour * 60 + A.start->wMinute;
	int B_time = B.start->wHour * 60 + B.start->wMinute;

	return A_time < B_time;
}

void BrodcastScher::DayEventView::UpdateUIEventList()
{
	std::sort(EventList.begin(), EventList.end(), EventSort);
	theList->Items->Clear();

	for (auto data : EventList) {
		theList->Items->Append(data.UIobject);
	}
}




