﻿//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BINDING_DEBUG_OUTPUT
extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent();
#endif

#include "ScheduleTab.xaml.h"

void ::BrodcastScher::ScheduleTab::InitializeComponent()
{
    if (_contentLoaded)
    {
        return;
    }
    _contentLoaded = true;
    ::Windows::Foundation::Uri^ resourceLocator = ref new ::Windows::Foundation::Uri(L"ms-appx:///ScheduleTab.xaml");
    ::Windows::UI::Xaml::Application::LoadComponent(this, resourceLocator, ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);
}

void ::BrodcastScher::ScheduleTab::Connect(int __connectionId, ::Platform::Object^ __target)
{
    switch (__connectionId)
    {
        case 1:
            {
                this->Calendar = safe_cast<::Windows::UI::Xaml::Controls::CalendarView^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::CalendarView^>(this->Calendar))->SelectedDatesChanged += ref new ::Windows::Foundation::TypedEventHandler<::Windows::UI::Xaml::Controls::CalendarView^, ::Windows::UI::Xaml::Controls::CalendarViewSelectedDatesChangedEventArgs^>(this, (void (::BrodcastScher::ScheduleTab::*)
                    (::Windows::UI::Xaml::Controls::CalendarView^, ::Windows::UI::Xaml::Controls::CalendarViewSelectedDatesChangedEventArgs^))&ScheduleTab::Calendar_SelectedDatesChanged);
                (safe_cast<::Windows::UI::Xaml::Controls::CalendarView^>(this->Calendar))->CalendarViewDayItemChanging += ref new ::Windows::Foundation::TypedEventHandler<::Windows::UI::Xaml::Controls::CalendarView^, ::Windows::UI::Xaml::Controls::CalendarViewDayItemChangingEventArgs^>(this, (void (::BrodcastScher::ScheduleTab::*)
                    (::Windows::UI::Xaml::Controls::CalendarView^, ::Windows::UI::Xaml::Controls::CalendarViewDayItemChangingEventArgs^))&ScheduleTab::Calendar_CalendarViewDayItemChanging);
            }
            break;
    }
    _contentLoaded = true;
}

::Windows::UI::Xaml::Markup::IComponentConnector^ ::BrodcastScher::ScheduleTab::GetBindingConnector(int __connectionId, ::Platform::Object^ __target)
{
    __connectionId;         // unreferenced
    __target;               // unreferenced
    return nullptr;
}

