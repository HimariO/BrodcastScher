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

#include "PlayerTab.xaml.h"

void ::BrodcastScher::PlayerTab::InitializeComponent()
{
    if (_contentLoaded)
    {
        return;
    }
    _contentLoaded = true;
    ::Windows::Foundation::Uri^ resourceLocator = ref new ::Windows::Foundation::Uri(L"ms-appx:///PlayerTab.xaml");
    ::Windows::UI::Xaml::Application::LoadComponent(this, resourceLocator, ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);
}


/// <summary>
/// Auto generated class for compiled bindings.
/// </summary>
class BrodcastScher::PlayerTab::PlayerTab_obj6_Bindings 
    : public ::XamlBindingInfo::XamlBindingsBase<::BrodcastScher::DayEvent>
{
public:
    PlayerTab_obj6_Bindings()
    {
    }

    void Connect(int __connectionId, ::Platform::Object^ __target)
    {
        switch(__connectionId)
        {
            case 6:
                this->obj6 = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(__target);
                break;
            case 7:
                this->obj7 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
                break;
            case 8:
                this->obj8 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
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
    ::Platform::WeakReference obj6;
    ::Windows::UI::Xaml::Controls::TextBlock^ obj7;
    ::Windows::UI::Xaml::Controls::TextBlock^ obj8;

    // Update methods for each path node used in binding steps.
    void Update_(::BrodcastScher::DayEvent^ obj, int phase)
    {
        if (obj != nullptr)
        {
            if ((phase & (NOT_PHASED | (1 << 0))) != 0)
            {
                this->Update_Color(obj->Color, phase);
                this->Update_In(obj->In, phase);
                this->Update_Out(obj->Out, phase);
            }
        }
    }
    void Update_Color(::Platform::String^ obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_Panel_Background(this->obj6.Resolve<::Windows::UI::Xaml::Controls::Grid>(), (::Windows::UI::Xaml::Media::Brush^) ::Windows::UI::Xaml::Markup::XamlBindingHelper::ConvertValue(::Windows::UI::Xaml::Media::Brush::typeid, obj), nullptr);
        }
    }
    void Update_In(::Platform::String^ obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_TextBlock_Text(this->obj7, obj, nullptr);
        }
    }
    void Update_Out(::Platform::String^ obj, int phase)
    {
        if((phase & ((1 << 0) | NOT_PHASED )) != 0)
        {
            ::XamlBindingInfo::XamlBindingSetters::Set_Windows_UI_Xaml_Controls_TextBlock_Text(this->obj8, obj, nullptr);
        }
    }
};

void ::BrodcastScher::PlayerTab::Connect(int __connectionId, ::Platform::Object^ __target)
{
    switch (__connectionId)
    {
        case 1:
            {
                this->LeastEventProgress = safe_cast<::Windows::UI::Xaml::Controls::ProgressBar^>(__target);
            }
            break;
        case 2:
            {
                this->btn_start = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Button^>(this->btn_start))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::BrodcastScher::PlayerTab::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&PlayerTab::btn_start_Click);
            }
            break;
        case 3:
            {
                this->btn_stop = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Button^>(this->btn_stop))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::BrodcastScher::PlayerTab::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&PlayerTab::btn_stop_Click);
            }
            break;
        case 4:
            {
                this->equalizerEffectContainer = safe_cast<::Windows::UI::Xaml::Controls::StackPanel^>(__target);
            }
            break;
        case 5:
            {
                this->remain_job_list = safe_cast<::Windows::UI::Xaml::Controls::ListView^>(__target);
            }
            break;
        case 9:
            {
                this->textbox_currentTime = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
            }
            break;
        case 10:
            {
                this->textbox_endTime = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
            }
            break;
        case 11:
            {
                this->textbox_startTime = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
            }
            break;
        case 12:
            {
                this->eqToggle = safe_cast<::Windows::UI::Xaml::Controls::ToggleSwitch^>(__target);
            }
            break;
        case 13:
            {
                this->eq1SliderContainer = safe_cast<::Windows::UI::Xaml::Controls::StackPanel^>(__target);
            }
            break;
        case 14:
            {
                this->eq2SliderContainer = safe_cast<::Windows::UI::Xaml::Controls::StackPanel^>(__target);
            }
            break;
        case 15:
            {
                this->eq3SliderContainer = safe_cast<::Windows::UI::Xaml::Controls::StackPanel^>(__target);
            }
            break;
        case 16:
            {
                this->eq4SliderContainer = safe_cast<::Windows::UI::Xaml::Controls::StackPanel^>(__target);
            }
            break;
        case 17:
            {
                this->eq5SliderContainer = safe_cast<::Windows::UI::Xaml::Controls::StackPanel^>(__target);
            }
            break;
        case 18:
            {
                this->eq6SliderContainer = safe_cast<::Windows::UI::Xaml::Controls::StackPanel^>(__target);
            }
            break;
        case 19:
            {
                this->eq6Slider = safe_cast<::Windows::UI::Xaml::Controls::Slider^>(__target);
            }
            break;
        case 20:
            {
                this->eq6SliderLabel = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
            }
            break;
        case 21:
            {
                this->eq5Slider = safe_cast<::Windows::UI::Xaml::Controls::Slider^>(__target);
            }
            break;
        case 22:
            {
                this->eq5SliderLabel = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
            }
            break;
        case 23:
            {
                this->eq4Slider = safe_cast<::Windows::UI::Xaml::Controls::Slider^>(__target);
            }
            break;
        case 24:
            {
                this->eq4SliderLabel = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
            }
            break;
        case 25:
            {
                this->eq3Slider = safe_cast<::Windows::UI::Xaml::Controls::Slider^>(__target);
            }
            break;
        case 26:
            {
                this->eq3SliderLabel = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
            }
            break;
        case 27:
            {
                this->eq2Slider = safe_cast<::Windows::UI::Xaml::Controls::Slider^>(__target);
            }
            break;
        case 28:
            {
                this->eq2SliderLabel = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
            }
            break;
        case 29:
            {
                this->eq1Slider = safe_cast<::Windows::UI::Xaml::Controls::Slider^>(__target);
            }
            break;
        case 30:
            {
                this->eq1SliderLabel = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
            }
            break;
    }
    _contentLoaded = true;
}

::Windows::UI::Xaml::Markup::IComponentConnector^ ::BrodcastScher::PlayerTab::GetBindingConnector(int __connectionId, ::Platform::Object^ __target)
{
    ::XamlBindingInfo::XamlBindings^ bindings = nullptr;
    switch (__connectionId)
    {
        case 6:
            {
                ::Windows::UI::Xaml::Controls::Grid^ element6 = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(__target);
                PlayerTab_obj6_Bindings* objBindings = new PlayerTab_obj6_Bindings();
                objBindings->SetDataRoot(element6->DataContext);
                bindings = ref new ::XamlBindingInfo::XamlBindings(objBindings);
                bindings->SubscribeForDataContextChanged(element6);
                ::Windows::UI::Xaml::DataTemplate::SetExtensionInstance(element6, bindings);
            }
            break;
    }
    return bindings;
}


