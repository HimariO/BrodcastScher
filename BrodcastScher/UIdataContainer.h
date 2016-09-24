#pragma once

using namespace Platform;
using json = nlohmann::json;


namespace BrodcastScher
{
	enum InputType { InputDevice, PlayList, AudioFile };
	class DayEventDetail;

	public ref class DayEvent  sealed {
	
		Platform::String ^rIn; //name
		Platform::String ^rOut; // description
		Platform::String ^rColor;
		double itemHeight;

	public:
		DayEvent(String^ A, String^ B, double h, String^ color);

		property String^ In {
			String^ get() { return this->rIn; };
			void set(String^ s) { this->rIn = s; };
		};

		property String^ Out {
			String^ get() {
				return this->rOut;
			};
			void set(String^ s) { this->rOut = s; };
		};

		property String^ Color {
			String^ get() {
				return this->rColor;
			};
			void set(String^ s) { this->rColor = s; };
		};

		property double itemH {
			double get() {
				return this->itemHeight;
			};
			void set(double s) { this->itemHeight = s; };
		};
	};


	class DayEventDetail {
	private:
		static  unsigned int counter_color;
		static  std::string color_opts[6];
	public:
		DayEventDetail();
		DayEventDetail(json JSON);
		json toJSON();

		DayEvent^ UIobject;
		DayEventDetail* Next ;
		//DayEventDetail* Beside;

		std::string event_name;
		std::string description;

		LPSYSTEMTIME start;
		LPSYSTEMTIME end;

		int repeat_type = 0;

		InputType type;
		unsigned int input_dev_index = 0;
		unsigned int output_dev_index = 0;
	};
}