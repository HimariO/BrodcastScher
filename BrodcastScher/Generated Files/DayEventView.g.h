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
                ref class TimePicker;
                ref class TextBox;
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
        class DayEventView_obj9_Bindings;
    
        ::XamlBindingInfo::XamlBindings^ Bindings;
        private: ::Windows::UI::Xaml::Controls::ListView^ OutputDevicesList;
        private: ::Windows::UI::Xaml::Controls::ListView^ InputDevicesList;
        private: ::Windows::UI::Xaml::Controls::TimePicker^ endTimePicker;
        private: ::Windows::UI::Xaml::Controls::TextBox^ endTimeSec;
        private: ::Windows::UI::Xaml::Controls::TimePicker^ startTimePicker;
        private: ::Windows::UI::Xaml::Controls::TextBox^ startTimeSec;
        private: ::Windows::UI::Xaml::Controls::ListView^ theList;
    };
}

