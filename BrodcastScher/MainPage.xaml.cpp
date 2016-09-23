//
// MainPage.xaml.cpp
// MainPage 類別的實作。
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "ScheduleTab.xaml.h"
#include "PlayerTab.xaml.h"

#include "CodeToolBox.h"

using namespace BrodcastScher;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::Graphics::Display;
using namespace Windows::UI::ViewManagement;

using json = nlohmann::json;

UIElement^ currTab = nullptr;
ScheduleTab^ SchTab;
PlayerTab^ playerTab;

json json_file;
String^ DefaultDeviceIdString;


void WriteToFile(std::string data) {

	String^ data_S = Tool::sToS(data);

	using namespace Windows::Storage;

	auto localFolder = ApplicationData::Current->LocalFolder;

	concurrency::create_task(localFolder->CreateFileAsync("data.json", Windows::Storage::CreationCollisionOption::ReplaceExisting))
		.then([data_S](StorageFile^ file) {
		try {
			FileIO::WriteTextAsync(file, data_S);
		}
		catch (Platform::COMException^ e) {
			auto mes = e->Message;
		}
	});
}


MainPage::MainPage()
{
	InitializeComponent();

	if (currTab == nullptr) {
		SchTab = ref new ScheduleTab();
		playerTab = ref new PlayerTab();

		currTab = playerTab;	
	}
	Content->Children->Append(currTab);

	using namespace Windows::Storage;

	if (json_file.empty()) {
		auto localFolder = ApplicationData::Current->LocalFolder;

		concurrency::create_task(localFolder->GetFileAsync("data.json")).then([this](StorageFile^ file) {
			try {
				return FileIO::ReadTextAsync(file);
			}
			catch (Platform::COMException^ e) {
				// Something when wrong.
			}
		}).then([this](concurrency::task<String^> task) {
			try {
				String^ data = task.get(); // getting task result.
				std::string data_s = Tool::STos(data);
				json_file = json::parse(data_s);

			}
			catch (std::domain_error e) {
				// Parse Error!
				// display Error Message somewhere.
			}
			catch (...) {
				// File not found!
				json_file = json::parse("{\"periodic\": { \"day\": [],\"week\": {}}, \"events\": {}}");
				WriteToFile(json_file.dump());
			}
		});
	}
}

void BrodcastScher::MainPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs ^ e)
{
	auto page_name = e->SourcePageType.Name;
	
	if (e->NavigationMode == NavigationMode::Back) {
		WriteToFile(json_file.dump());
	}
}


void BrodcastScher::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto btn = (Button^)sender;
	auto btn_name = btn->Name;

	Content->Children->Clear();
	
	if(btn_name == "MenuButton_CurrentJob")
		currTab = playerTab;
	else if (btn_name == "MenuButton_Schedule")
		currTab = SchTab;
	else if (btn_name == "MenuButton_PlayList")
		currTab = playerTab;
	else
		currTab = playerTab;

	Content->Children->Append(currTab);
}



void BrodcastScher::MainPage::Page_Unloaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	
}
