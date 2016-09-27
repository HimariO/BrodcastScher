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

#include "DayEventView.xaml.h"

void ::BrodcastScher::DayEventView::InitializeComponent()
{
    if (_contentLoaded)
    {
        return;
    }
    _contentLoaded = true;
    ::Windows::Foundation::Uri^ resourceLocator = ref new ::Windows::Foundation::Uri(L"ms-appx:///DayEventView.xaml");
    ::Windows::UI::Xaml::Application::LoadComponent(this, resourceLocator, ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);
}


/// <summary>
/// Auto generated class for compiled bindings.
/// </summary>
class BrodcastScher::DayEventView::DayEventView_obj26_Bindings 
    : public ::XamlBindingInfo::XamlBindingsBase<::BrodcastScher::DayEvent>
{
public:
    DayEventView_obj26_Bindings()
    {
    }

    void Connect(int __connectionId, ::Platform::Object^ __target)
    {
        switch(__connectionId)
        {
            case 26:
                this->obj26 = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(__target);
                break;
            case 27:
                this->obj27 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
                break;
            case 28:
                this->obj28 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
                break;
        }
    }

    void ResetTemplate()
    {
    }

    int ProcessBindings(::Windows::UI::Xaml::Controls::ContainerContentChangingEventArgs^ args)
    {
        int nextPhase = -1;
        switch(args->Phase)
        {
            case 0:
                nextPhase = -1;
                this->SetDataRoot(static_cast<::BrodcastScher::DayEvent^>(args->Item));
                if (this->_dataContextChangedToken.Value != 0)
                {
                    safe_cast<::Windows::UI::Xaml::FrameworkElement^>(args->ItemContainer->ContentTemplateRoot)->DataContextChanged -= this->_dataContextChangedToken;
                    this->_dataContextChangedToken.Value = 0;
                }
                this->_isInitialized = true;
                break;
        }
        this->Update_((::BrodcastScher::DayEvent^) args->Item, (1 << args->Phase));
        return nextPhase;
    }
private:
    // Fields for each control that has bindings.
    ::Platform::WeakReference obj26;
    ::Windows::UI::Xaml::Controls::TextBlock^ obj27;
    ::Windows::UI::Xaml::Controls::TextBlock^ obj28;

    // Update methods for each path node used in binding steps.
    void Update_(::BrodcastScher::DayEvent^ obj, int phase)
    {
        if (obj != nullptr)
        {
            if ((phase & (NOT_PHASED | (1 << 0))) != 0)
            {
                this->Update_itemH(obj->itemH, phase);
                this->Update_Color(obj->Color, phase);
                this->Update_In(obj->In, phase);
                this->Update_Out(obj->Out, phase);
            }
        }
    }
    void Update_itemH(::default::float64 obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_FrameworkElement_Height(this->obj26.Resolve<::Windows::UI::Xaml::Controls::Grid>(), obj);
        }
    }
    void Update_Color(::Platform::String^ obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_Panel_Background(this->obj26.Resolve<::Windows::UI::Xaml::Controls::Grid>(), (::Windows::UI::Xaml::Media::Brush^) ::Windows::UI::Xaml::Markup::XamlBindingHelper::ConvertValue(::Windows::UI::Xaml::Media::Brush::typeid, obj), nullptr);
        }
    }
    void Update_In(::Platform::String^ obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_TextBlock_Text(this->obj27, obj, nullptr);
        }
    }
    void Update_Out(::Platform::String^ obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_TextBlock_Text(this->obj28, obj, nullptr);
        }
    }
};

void ::BrodcastScher::DayEventView::Connect(int __connectionId, ::Platform::Object^ __target)
{
    switch (__connectionId)
    {
        case 1:
            {
                ::Windows::UI::Xaml::Controls::MenuFlyoutItem^ element1 = safe_cast<::Windows::UI::Xaml::Controls::MenuFlyoutItem^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::MenuFlyoutItem^>(element1))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&DayEventView::MenuFlyoutItem_Click);
            }
            break;
        case 2:
            {
                ::Windows::UI::Xaml::Controls::MenuFlyoutItem^ element2 = safe_cast<::Windows::UI::Xaml::Controls::MenuFlyoutItem^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::MenuFlyoutItem^>(element2))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&DayEventView::MenuFlyoutItem_Click);
            }
            break;
        case 3:
            {
                ::Windows::UI::Xaml::Controls::MenuFlyoutItem^ element3 = safe_cast<::Windows::UI::Xaml::Controls::MenuFlyoutItem^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::MenuFlyoutItem^>(element3))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&DayEventView::MenuFlyoutItem_Click);
            }
            break;
        case 4:
            {
                ::Windows::UI::Xaml::Controls::Button^ element4 = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Button^>(element4))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&DayEventView::Button_Click);
            }
            break;
        case 5:
            {
                ::Windows::UI::Xaml::Controls::Button^ element5 = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Button^>(element5))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&DayEventView::Button_Click_2);
            }
            break;
        case 6:
            {
                ::Windows::UI::Xaml::Controls::Button^ element6 = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Button^>(element6))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&DayEventView::Button_Click_1);
            }
            break;
        case 7:
            {
                this->OutputDevicesList = safe_cast<::Windows::UI::Xaml::Controls::ListView^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::ListView^>(this->OutputDevicesList))->ItemClick += ref new ::Windows::UI::Xaml::Controls::ItemClickEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::Controls::ItemClickEventArgs^))&DayEventView::DevicesList_ItemClick);
            }
            break;
        case 8:
            {
                this->textbox_FilePath = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
            }
            break;
        case 9:
            {
                this->InputDevicesList = safe_cast<::Windows::UI::Xaml::Controls::ListView^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::ListView^>(this->InputDevicesList))->ItemClick += ref new ::Windows::UI::Xaml::Controls::ItemClickEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::Controls::ItemClickEventArgs^))&DayEventView::DevicesList_ItemClick);
            }
            break;
        case 10:
            {
                this->contentTag_PGM = safe_cast<::Windows::UI::Xaml::Controls::CheckBox^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::CheckBox^>(this->contentTag_PGM))->Checked += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&DayEventView::contentTag_PGM_Checked);
            }
            break;
        case 11:
            {
                this->contentTag_AD = safe_cast<::Windows::UI::Xaml::Controls::CheckBox^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::CheckBox^>(this->contentTag_AD))->Checked += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&DayEventView::contentTag_PGM_Checked);
            }
            break;
        case 12:
            {
                this->check_FileInput = safe_cast<::Windows::UI::Xaml::Controls::CheckBox^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::CheckBox^>(this->check_FileInput))->Checked += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&DayEventView::check_FileInput_Checked);
            }
            break;
        case 13:
            {
                this->check_Deviceinput = safe_cast<::Windows::UI::Xaml::Controls::CheckBox^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::CheckBox^>(this->check_Deviceinput))->Checked += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&DayEventView::check_FileInput_Checked);
            }
            break;
        case 14:
            {
                this->check_PlayListInput = safe_cast<::Windows::UI::Xaml::Controls::CheckBox^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::CheckBox^>(this->check_PlayListInput))->Checked += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&DayEventView::check_FileInput_Checked);
            }
            break;
        case 15:
            {
                this->check_EveryDay = safe_cast<::Windows::UI::Xaml::Controls::CheckBox^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::CheckBox^>(this->check_EveryDay))->Checked += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&DayEventView::check_EveryDay_Checked);
            }
            break;
        case 16:
            {
                this->check_EveryWeek = safe_cast<::Windows::UI::Xaml::Controls::CheckBox^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::CheckBox^>(this->check_EveryWeek))->Checked += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&DayEventView::check_EveryDay_Checked);
            }
            break;
        case 17:
            {
                this->endTimeH = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(this->endTimeH))->TextChanged += ref new ::Windows::UI::Xaml::Controls::TextChangedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::Controls::TextChangedEventArgs^))&DayEventView::endTimeSec_TextChanged);
            }
            break;
        case 18:
            {
                this->endTimeM = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(this->endTimeM))->TextChanged += ref new ::Windows::UI::Xaml::Controls::TextChangedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::Controls::TextChangedEventArgs^))&DayEventView::endTimeSec_TextChanged);
            }
            break;
        case 19:
            {
                this->endTimeS = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(this->endTimeS))->TextChanged += ref new ::Windows::UI::Xaml::Controls::TextChangedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::Controls::TextChangedEventArgs^))&DayEventView::endTimeSec_TextChanged);
            }
            break;
        case 20:
            {
                this->startTimeH = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(this->startTimeH))->TextChanged += ref new ::Windows::UI::Xaml::Controls::TextChangedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::Controls::TextChangedEventArgs^))&DayEventView::startTimeSec_TextChanged);
            }
            break;
        case 21:
            {
                this->startTimeM = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(this->startTimeM))->TextChanged += ref new ::Windows::UI::Xaml::Controls::TextChangedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::Controls::TextChangedEventArgs^))&DayEventView::startTimeSec_TextChanged);
            }
            break;
        case 22:
            {
                this->startTimeS = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(this->startTimeS))->TextChanged += ref new ::Windows::UI::Xaml::Controls::TextChangedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::Controls::TextChangedEventArgs^))&DayEventView::startTimeSec_TextChanged);
            }
            break;
        case 23:
            {
                this->textbox_eventName = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(this->textbox_eventName))->TextChanged += ref new ::Windows::UI::Xaml::Controls::TextChangedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::Controls::TextChangedEventArgs^))&DayEventView::textbox_eventName_TextChanged);
            }
            break;
        case 24:
            {
                this->theList = safe_cast<::Windows::UI::Xaml::Controls::ListView^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::ListView^>(this->theList))->ItemClick += ref new ::Windows::UI::Xaml::Controls::ItemClickEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::Controls::ItemClickEventArgs^))&DayEventView::theList_ItemClick);
            }
            break;
        case 25:
            {
                this->btn_AddEvent = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Button^>(this->btn_AddEvent))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&DayEventView::btn_AddEvent_Click);
            }
            break;
        case 26:
            {
                ::Windows::UI::Xaml::Controls::Grid^ element26 = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Grid^>(element26))->RightTapped += ref new ::Windows::UI::Xaml::Input::RightTappedEventHandler(this, (void (::BrodcastScher::DayEventView::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::Input::RightTappedRoutedEventArgs^))&DayEventView::Grid_RightTapped);
            }
            break;
    }
    _contentLoaded = true;
}

::Windows::UI::Xaml::Markup::IComponentConnector^ ::BrodcastScher::DayEventView::GetBindingConnector(int __connectionId, ::Platform::Object^ __target)
{
    ::XamlBindingInfo::XamlBindings^ bindings = nullptr;
    switch (__connectionId)
    {
        case 26:
            {
                ::Windows::UI::Xaml::Controls::Grid^ element26 = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(__target);
                DayEventView_obj26_Bindings* objBindings = new DayEventView_obj26_Bindings();
                objBindings->SetDataRoot(element26->DataContext);
                bindings = ref new ::XamlBindingInfo::XamlBindings(objBindings);
                bindings->SubscribeForDataContextChanged(element26);
                ::Windows::UI::Xaml::DataTemplate::SetExtensionInstance(element26, bindings);
            }
            break;
    }
    return bindings;
}


