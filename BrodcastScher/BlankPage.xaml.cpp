//
// BlankPage.xaml.cpp
// BlankPage 類別的實作
//

#include "pch.h"
#include "BlankPage.xaml.h"


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


BlankPage::BlankPage()
{
	InitializeComponent();
	theList->Items->Append(ref new DayEvent("A", "B", 50, "#FF82FFF4"));
	//theList->Items->Append(ref new DayEvent("A", "B", 100));
	//theList->Items->Append(ref new DayEvent("A", "B", 150));
	InitAudioGraphSetting();
}


void BrodcastScher::BlankPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	//theList->Items->Append(ref new DayEvent("c", "C", 100));
	this->Frame->GoBack();
}


void BlankPage::InitAudioGraphSetting() {
	graph_setting = ref new AudioGraphSettings(AudioRenderCategory::Media);
	graph_setting->QuantumSizeSelectionMode = QuantumSizeSelectionMode::LowestLatency;

	concurrency::create_task(DeviceInformation::FindAllAsync()).then([this](DeviceInformationCollection^ devices) {
		this->DeviceList = devices;
		
		//add to list view or something... 
	}); 
}