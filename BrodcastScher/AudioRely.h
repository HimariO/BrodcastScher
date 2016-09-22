#pragma once

#include "pch.h"

using namespace Windows::Media::MediaProperties;
using namespace Windows::Media::Devices;
using namespace Windows::Media::Audio;
using namespace Windows::Media::Render;
using namespace Windows::Media::Capture;
using namespace Windows::Devices::Enumeration;

class AudioRely {
public:
	AudioRely(int device_index_i, int device_index_o){
		// Get Input/output DeiveceInfo by Index;
		concurrency::create_task(DeviceInformation::FindAllAsync(MediaDevice::GetAudioCaptureSelector())).then(
		[this, device_index_i](DeviceInformationCollection^ devices) {
			this->DeviceList = devices;
			if (devices->Size > device_index_i)
				In_Dev_info = devices->GetAt(device_index_i);
			
			return DeviceInformation::FindAllAsync(MediaDevice::GetAudioRenderSelector());
		}).then(
		[this, device_index_o](concurrency::task<DeviceInformationCollection^> task) {
			auto devices = task.get();
			
			if (devices->Size > device_index_o)
				Out_Dev_info = devices->GetAt(device_index_o);
			
		}).then([this]() { initGraph(); });
		
	}

	~AudioRely() {

	}


	void StartStreaming() {
		aGraph->Start();
	}


	void StopStreaming() {
		aGraph->Stop();
	}


private:
	AudioGraph^ aGraph= nullptr;

	AudioDeviceInputNode^ inputNode = nullptr;
	AudioDeviceOutputNode^ outputNode = nullptr;

	DeviceInformationCollection^ DeviceList;
	DeviceInformation^ In_Dev_info;
	DeviceInformation^ Out_Dev_info;
	

	void initGraph() {
		AudioGraphSettings^ graph_setting = ref new AudioGraphSettings(AudioRenderCategory::Media);
		graph_setting->QuantumSizeSelectionMode = QuantumSizeSelectionMode::LowestLatency;
		graph_setting->PrimaryRenderDevice = Out_Dev_info;
		

		concurrency::create_task(AudioGraph::CreateAsync(graph_setting)).then(
			[this](CreateAudioGraphResult^ result) {
				if(result->Status != AudioGraphCreationStatus::Success){
					switch (result->Status) {
					case AudioGraphCreationStatus::DeviceNotAvailable:

						break;
					}
					return;
				}

				this->aGraph = result->Graph;
				
				concurrency::create_task(aGraph->CreateDeviceInputNodeAsync(MediaCategory::Media, aGraph->EncodingProperties, In_Dev_info)).then(
					[this](CreateAudioDeviceInputNodeResult^ node_result) {
					auto a = node_result->Status;
						switch (node_result->Status) {
						case AudioDeviceNodeCreationStatus::Success:
							inputNode = node_result->DeviceInputNode;
							return aGraph->CreateDeviceOutputNodeAsync();

						case AudioDeviceNodeCreationStatus::DeviceNotAvailable:

							break;
						case AudioDeviceNodeCreationStatus::FormatNotSupported:

							break;

						case AudioDeviceNodeCreationStatus::AccessDenied:

							break;

						case AudioDeviceNodeCreationStatus::UnknownFailure:

							break;
						}
						
					}
				).then(
					[this](concurrency::task<CreateAudioDeviceOutputNodeResult^> task) {
						auto node_result = task.get();
						outputNode = node_result->DeviceOutputNode;
					}
				).then(
					[this]() {
						inputNode->AddOutgoingConnection(outputNode);
					}
				);
			}
		);
	}

};