//
// PlayerTab.xaml.cpp
// PlayerTab 類別的實作
//

#include "pch.h"
#include "PlayerTab.xaml.h"

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

PlayerTab::PlayerTab()
{
	InitializeComponent();

	concurrency::create_task(DeviceInformation::FindAllAsync(MediaDevice::GetAudioCaptureSelector())).then(
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
	});
	

	using namespace Windows::System::Threading;
	using namespace Windows::UI::Core;
	TimeSpan delay;
	delay.Duration = 3 * 60 * 10000000; // 10,000,000 ticks per second

	ThreadPoolTimer ^ DelayTimer = ThreadPoolTimer::CreateTimer(
		ref new TimerElapsedHandler([this](ThreadPoolTimer^ source)
	{
		// 
		// TODO: Work
		// 

		// 
		// Update the UI thread by using the UI core dispatcher.
		// 
		Dispatcher->RunAsync(CoreDispatcherPriority::High,
			ref new DispatchedHandler([this]()
		{
			// 
			// UI components can be accessed within this scope.
			// 

			

		}));

	}), delay);
}


void BrodcastScher::PlayerTab::btn_start_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	
	rely->StartStreaming();
}

void BrodcastScher::PlayerTab::InitAudioGraphSetting()
{
	rely->StopStreaming();
}


void BrodcastScher::PlayerTab::btn_deviceSet_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	rely = new AudioRely(input_listbox->SelectedIndex, output_listbox->SelectedIndex);
}
