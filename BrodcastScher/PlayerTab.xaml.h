﻿//
// PlayerTab.xaml.h
// PlayerTab 類別的宣告
//

#pragma once

#include "PlayerTab.g.h"
#include "AudioRely.h"
#include <vector>

using json = nlohmann::json;
extern json json_file;

namespace BrodcastScher
{
	/// <summary>
	/// 可以在本身使用或巡覽至框架內的空白頁面。
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class PlayerTab sealed
	{
	public:
		PlayerTab();
	private:
		AudioRely* rely;
		bool auto_start = false;
		std::vector<Platform::String^> DeviceList_out;
		std::vector<Platform::String^> DeviceList_in;

		std::vector<DayEventDetail*> event_queue;
		DayEventDetail * least_started_event;

		std::vector<concurrency::task<bool>> onGoingTask;
		std::vector<AudioRely*> onGoingRely;

		void btn_start_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void btn_deviceSet_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void btn_stop_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		void InitEventQueue();
		concurrency::task<void> CreateUpdateTask();
		void eqToggle_Toggled(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void eq1Slider_ValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ e);
		void limiterToggle_Toggled(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
