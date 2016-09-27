//
// ScheduleTab.xaml.h
// ScheduleTab 類別的宣告
//

#pragma once
#include "ScheduleTab.g.h"

using json = nlohmann::json;

extern json json_file;

namespace BrodcastScher
{
	/// <summary>
	/// 可以在本身使用或巡覽至框架內的空白頁面。
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class ScheduleTab sealed
	{
	public:
		ScheduleTab();
		void PassNavigate(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e);

	protected:

		void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

	private:
		

		void Calendar_SelectedDatesChanged(Windows::UI::Xaml::Controls::CalendarView^ sender, Windows::UI::Xaml::Controls::CalendarViewSelectedDatesChangedEventArgs^ args);
		void Calendar_CalendarViewDayItemChanging(Windows::UI::Xaml::Controls::CalendarView^ sender, Windows::UI::Xaml::Controls::CalendarViewDayItemChangingEventArgs^ args);
		void Calendar_RightTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::RightTappedRoutedEventArgs^ e);
	};
}
