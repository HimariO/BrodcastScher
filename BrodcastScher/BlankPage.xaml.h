//
// BlankPage.xaml.h
// BlankPage 類別的宣告
//

#pragma once

#include "BlankPage.g.h"
#include "UIdataContainer.h"

namespace BrodcastScher
{
	/// <summary>
	/// 可以在本身使用或巡覽至框架內的空白頁面。
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class BlankPage sealed
	{
	public:
		BlankPage();
		
	private:
		Windows::Media::Audio::AudioGraphSettings^ graph_setting = nullptr;
		Windows::Devices::Enumeration::DeviceInformationCollection^ DeviceList;

		void Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void InitAudioGraphSetting();
	};
}
