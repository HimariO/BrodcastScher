﻿//
// PlayerTab.xaml.h
// PlayerTab 類別的宣告
//

#pragma once

#include "PlayerTab.g.h"
#include "AudioRely.h"
#include <queue>

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
		std::queue<DayEventDetail> event_queue;

		void btn_start_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void InitAudioGraphSetting();
		void btn_deviceSet_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
