﻿#pragma once
//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------

#include "XamlBindingInfo.g.h"

namespace Windows {
    namespace UI {
        namespace Xaml {
            namespace Controls {
                ref class ListView;
                ref class TextBlock;
                ref class CheckBox;
                ref class TextBox;
                ref class Button;
            }
        }
    }
}

namespace BrodcastScher
{
    [::Windows::Foundation::Metadata::WebHostHidden]
    partial ref class DayEventView : public ::Windows::UI::Xaml::Controls::Page, 
        public ::Windows::UI::Xaml::Markup::IComponentConnector,
        public ::Windows::UI::Xaml::Markup::IComponentConnector2
    {
    public:
        void InitializeComponent();
        virtual void Connect(int connectionId, ::Platform::Object^ target);
        virtual ::Windows::UI::Xaml::Markup::IComponentConnector^ GetBindingConnector(int connectionId, ::Platform::Object^ target);
    
    private:
        bool _contentLoaded;
        class DayEventView_obj27_Bindings;
    
        ::XamlBindingInfo::XamlBindings^ Bindings;
        private: ::Windows::UI::Xaml::Controls::ListView^ OutputDevicesList;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ textbox_FilePath;
        private: ::Windows::UI::Xaml::Controls::ListView^ InputDevicesList;
        private: ::Windows::UI::Xaml::Controls::CheckBox^ contentTag_PGM;
        private: ::Windows::UI::Xaml::Controls::CheckBox^ contentTag_AD;
        private: ::Windows::UI::Xaml::Controls::CheckBox^ check_FileInput;
        private: ::Windows::UI::Xaml::Controls::CheckBox^ check_Deviceinput;
        private: ::Windows::UI::Xaml::Controls::CheckBox^ check_PlayListInput;
        private: ::Windows::UI::Xaml::Controls::CheckBox^ check_EveryDay;
        private: ::Windows::UI::Xaml::Controls::CheckBox^ check_EveryWeek;
        private: ::Windows::UI::Xaml::Controls::TextBox^ endTimeH;
        private: ::Windows::UI::Xaml::Controls::TextBox^ endTimeM;
        private: ::Windows::UI::Xaml::Controls::TextBox^ endTimeS;
        private: ::Windows::UI::Xaml::Controls::TextBox^ startTimeH;
        private: ::Windows::UI::Xaml::Controls::TextBox^ startTimeM;
        private: ::Windows::UI::Xaml::Controls::TextBox^ startTimeS;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ textbox_Date;
        private: ::Windows::UI::Xaml::Controls::TextBox^ textbox_eventName;
        private: ::Windows::UI::Xaml::Controls::ListView^ theList;
        private: ::Windows::UI::Xaml::Controls::Button^ btn_AddEvent;
    };
}

