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
                ref class ProgressBar;
                ref class Button;
                ref class StackPanel;
                ref class ListView;
                ref class TextBlock;
                ref class ToggleSwitch;
                ref class Slider;
            }
        }
    }
}

namespace BrodcastScher
{
    [::Windows::Foundation::Metadata::WebHostHidden]
    partial ref class PlayerTab : public ::Windows::UI::Xaml::Controls::Page, 
        public ::Windows::UI::Xaml::Markup::IComponentConnector,
        public ::Windows::UI::Xaml::Markup::IComponentConnector2
    {
    public:
        void InitializeComponent();
        virtual void Connect(int connectionId, ::Platform::Object^ target);
        virtual ::Windows::UI::Xaml::Markup::IComponentConnector^ GetBindingConnector(int connectionId, ::Platform::Object^ target);
    
    private:
        bool _contentLoaded;
        class PlayerTab_obj6_Bindings;
    
        ::XamlBindingInfo::XamlBindings^ Bindings;
        private: ::Windows::UI::Xaml::Controls::ProgressBar^ LeastEventProgress;
        private: ::Windows::UI::Xaml::Controls::Button^ btn_start;
        private: ::Windows::UI::Xaml::Controls::Button^ btn_stop;
        private: ::Windows::UI::Xaml::Controls::StackPanel^ equalizerEffectContainer;
        private: ::Windows::UI::Xaml::Controls::ListView^ remain_job_list;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ textbox_currentTime;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ textbox_endTime;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ textbox_startTime;
        private: ::Windows::UI::Xaml::Controls::ToggleSwitch^ eqToggle;
        private: ::Windows::UI::Xaml::Controls::StackPanel^ eq1SliderContainer;
        private: ::Windows::UI::Xaml::Controls::StackPanel^ eq2SliderContainer;
        private: ::Windows::UI::Xaml::Controls::StackPanel^ eq3SliderContainer;
        private: ::Windows::UI::Xaml::Controls::StackPanel^ eq4SliderContainer;
        private: ::Windows::UI::Xaml::Controls::StackPanel^ eq5SliderContainer;
        private: ::Windows::UI::Xaml::Controls::StackPanel^ eq6SliderContainer;
        private: ::Windows::UI::Xaml::Controls::Slider^ eq6Slider;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ eq6SliderLabel;
        private: ::Windows::UI::Xaml::Controls::Slider^ eq5Slider;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ eq5SliderLabel;
        private: ::Windows::UI::Xaml::Controls::Slider^ eq4Slider;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ eq4SliderLabel;
        private: ::Windows::UI::Xaml::Controls::Slider^ eq3Slider;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ eq3SliderLabel;
        private: ::Windows::UI::Xaml::Controls::Slider^ eq2Slider;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ eq2SliderLabel;
        private: ::Windows::UI::Xaml::Controls::Slider^ eq1Slider;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ eq1SliderLabel;
    };
}

