﻿//
// ScheduleTab.xaml.cpp
// ScheduleTab 類別的實作
//

#include "pch.h"
#include <codecvt>
#include "ScheduleTab.xaml.h"
#include "DayEventView.xaml.h"
#include "CodeToolBox.h"
//#include "UIdataContainer.h"

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
using namespace Windows::Globalization::DateTimeFormatting;
using namespace Windows::Globalization;

DateTimeFormatter ^time_formater;
Calendar^ calendar;
std::vector<DayEventDetail> copyedDetail;
std::map<std::string, Windows::UI::Xaml::Controls::CalendarViewDayItem^> dayItems;

struct ColorEqual : public std::binary_function<const Color, const Color, bool>
{
	bool operator()(const Color& _Left, const Color& _Right) const
	{
		return (_Left.A == _Right.A) && (_Left.R == _Right.R) && (_Left.G == _Right.G) && (_Left.B == _Right.B);
	};
};


ScheduleTab::ScheduleTab()
{
	InitializeComponent();
	time_formater = ref new DateTimeFormatter("shortdate"); 
	calendar = ref new  Windows::Globalization::Calendar();

	calendar->SetToNow();
	calendar->Day = calendar->FirstDayInThisMonth;
	Calendar->MinDate = calendar->GetDateTime();

	calendar->SetToNow();
	calendar->AddMonths(2);
	calendar->Day = calendar->LastDayInThisMonth;
	Calendar->MaxDate = calendar->GetDateTime();
}

void BrodcastScher::ScheduleTab::PassNavigate(Windows::UI::Xaml::Navigation::NavigationEventArgs ^ e)
{
	OnNavigatedTo(e);
}


void BrodcastScher::ScheduleTab::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs ^ e)
{
	if (e->NavigationMode == NavigationMode::Back) {
		
		auto date = Calendar->SelectedDates->GetAt(0);
		calendar->SetDateTime(date);

		auto d = calendar->Day;
		auto m = calendar->Month;
		auto y = calendar->Year;
		auto s_date = Tool::GetDateString(y, m, d);

		if (dayItems.find(s_date) == dayItems.end())
			return;

		try {
			int item_num = json_file["events"][s_date].size();

			IVector<Color>^ colors = ref new Vector<Color, ColorEqual>();

			for (size_t i = 1; i <= item_num; i++)
			{
				if (i <= 3) {
					colors->Append(Windows::UI::Colors::Blue);
				}
				else if (i > 3 && i <= 6) {
					colors->Append(Windows::UI::Colors::Green);
				}
				else if (i > 6 && i <= 9) {
					colors->Append(Windows::UI::Colors::GreenYellow);
				}
				else if (i > 9) {
					colors->Append(Windows::UI::Colors::Red);
				}
			}


			dayItems[s_date]->SetDensityColors(colors);
		}
		catch (...) {}
	}
}


void BrodcastScher::ScheduleTab::Calendar_SelectedDatesChanged(Windows::UI::Xaml::Controls::CalendarView^ sender, Windows::UI::Xaml::Controls::CalendarViewSelectedDatesChangedEventArgs^ args)
{

	DateTime m_date;
	if (args->AddedDates->Size == 1) {
		m_date = args->AddedDates->GetAt(0);
		auto frame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Window::Current->Content);
		frame->Navigate(TypeName(DayEventView::typeid), m_date);
	}

}


void BrodcastScher::ScheduleTab::Calendar_CalendarViewDayItemChanging(Windows::UI::Xaml::Controls::CalendarView^ sender, Windows::UI::Xaml::Controls::CalendarViewDayItemChangingEventArgs^ args)
{
	calendar->SetDateTime(args->Item->Date);
	
	auto d = calendar->Day;
	auto m = calendar->Month;
	auto y = calendar->Year;
	auto weekday = Tool::STos(calendar->DayOfWeek.ToString());
	
	std::string s_time = Tool::GetDateString(y, m, d);
	int item_c = 0;

	try {
		if (json_file["events"].find(s_time) != json_file["events"].end()) {
			auto day_items = json_file["events"][s_time];

			if (day_items.size() > 0) {
				item_c += day_items.size();
			}
		}
	}catch(...){}

	try {
		if (json_file["periodic"]["week"].find(weekday) != json_file["periodic"]["week"].end()) {
			auto day_items = json_file["periodic"]["week"][weekday];

			if (day_items.size() > 0) {
				item_c += day_items.size();
			}
		}
	}
	catch (...) {}


	IVector<Color>^ colors = ref new Vector<Color, ColorEqual>();

	for (size_t i = 1; i <= item_c; i++)
	{
		if (i <= 3) {
			colors->Append(Windows::UI::Colors::Blue);
		}
		else if (i > 3 && i <= 6) {
			colors->Append(Windows::UI::Colors::Green);
		}
		else if (i > 6 && i <= 9) {
			colors->Append(Windows::UI::Colors::GreenYellow);
		}
		else if (i > 9) {
			colors->Append(Windows::UI::Colors::Red);
		}
	}
	
	args->Item->SetDensityColors(colors);

	if(d % 2 == 0) // Give event date some Color.
		args->Item->Background = ref new SolidColorBrush(Windows::UI::Colors::LightBlue);
	else
		args->Item->Background = ref new SolidColorBrush(Windows::UI::Colors::White);

	dayItems[s_time] = args->Item;
}




void BrodcastScher::ScheduleTab::Calendar_RightTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::RightTappedRoutedEventArgs^ e)
{

	auto calendar = (CalendarView^)sender;

	auto ContextMenu = (MenuFlyout^) this->Resources->Lookup("mContextMenu");
	ContextMenu->ShowAt(nullptr, e->GetPosition(nullptr));
}
