﻿//
// DayEventView.xaml.h
// DayEventView 類別的宣告
//

#pragma once

#include "DayEventView.g.h"
#include "UIdataContainer.h"
#include <vector>

using json = nlohmann::json;

extern json json_file;

namespace BrodcastScher
{
	/// <summary>
	/// 可以在本身使用或巡覽至框架內的空白頁面。
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class DayEventView sealed
	{
	public:
		DayEventView();
	private:
		Platform::Collections::Vector<Platform::String^> DeviceNames;
		std::vector<DayEventDetail> EventList;
		//DayEventDetail* EventSelected;

		void Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void DevicesList_ItemClick(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e);
		void startTimePicker_TimeChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TimePickerValueChangedEventArgs^ e);
		void endTimePicker_TimeChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TimePickerValueChangedEventArgs^ e);
		void EnumerateAudioDevicesAsync();
		void startTimeSec_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e);
		void endTimeSec_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e);

	protected:
		void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		void UpdateUIEventList();
	};
}