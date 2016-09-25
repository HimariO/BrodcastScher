#pragma once

#include "pch.h"

using namespace Windows::Media::MediaProperties;
using namespace Windows::Media::Devices;
using namespace Windows::Media::Audio;
using namespace Windows::Media::Render;
using namespace Windows::Media::Capture;
using namespace Windows::Devices::Enumeration;
using namespace Windows::Storage;

class AudioRely {
public:
	AudioRely(int device_index_i, int device_index_o, bool start_after_finish){
		// Get Input/output DeiveceInfo by Index;
		auto init_task = concurrency::create_task(DeviceInformation::FindAllAsync(MediaDevice::GetAudioCaptureSelector())).then(
		[this, device_index_i](DeviceInformationCollection^ devices) {
			//this->DeviceList = devices;
			if (devices->Size > device_index_i)
				In_Dev_info = devices->GetAt(device_index_i);
			
			return DeviceInformation::FindAllAsync(MediaDevice::GetAudioRenderSelector());
		}).then(
		[this, device_index_o](concurrency::task<DeviceInformationCollection^> task) {
			auto devices = task.get();
			
			if (devices->Size > device_index_o)
				Out_Dev_info = devices->GetAt(device_index_o);
			
		})
		.then([this]() { initGraph().wait(); })
		.then([this, start_after_finish]() { 
			if (start_after_finish)
				StartStreaming(); 
		});
	}


	AudioRely(std::wstring inputfile_path, int device_index_o, bool start_after_finish) {
		// Get Input/output DeiveceInfo by Index;
		auto init_task = concurrency::create_task(DeviceInformation::FindAllAsync(MediaDevice::GetAudioRenderSelector())).then(
			[this, device_index_o, inputfile_path](concurrency::task<DeviceInformationCollection^> task) {
			auto devices = task.get();

			if (devices->Size > device_index_o)
				Out_Dev_info = devices->GetAt(device_index_o);

			return StorageFile::GetFileFromPathAsync(ref new Platform::String(inputfile_path.c_str()));
		})
		.then([this](concurrency::task<StorageFile^> taskF) {
			try {
				AudioFile = taskF.get();
				
			}
			catch (...) { concurrency::cancel_current_task(); }
		})
		.then([this]() { initGraphWithFile().wait(); })
		.then([this, start_after_finish]() {
			if (start_after_finish)
				StartStreaming();
		});
	}

	~AudioRely() {

	}


	//bool operator==(const AudioRely& B) const {
	//	if (this == &B)
	//		return true;
	//	return false;
	//};

	void StartStreaming() {
		if(aGraph != nullptr)
			aGraph->Start();
	}


	void StopStreaming() {
		if (aGraph != nullptr)
			aGraph->Stop();
	}


private:
	AudioGraph^ aGraph= nullptr;

	AudioDeviceInputNode^ inputNode = nullptr;
	AudioFileInputNode^ fileNode = nullptr;
	AudioDeviceOutputNode^ outputNode = nullptr;

	DeviceInformationCollection^ DeviceList;
	DeviceInformation^ In_Dev_info;
	DeviceInformation^ Out_Dev_info;
	StorageFile^ AudioFile;

	concurrency::task<void> initGraphWithFile() {
		AudioGraphSettings^ graph_setting = ref new AudioGraphSettings(AudioRenderCategory::Media);
		graph_setting->QuantumSizeSelectionMode = QuantumSizeSelectionMode::LowestLatency;
		graph_setting->PrimaryRenderDevice = Out_Dev_info;
		

		return concurrency::create_task(AudioGraph::CreateAsync(graph_setting)).then(
			[this](CreateAudioGraphResult^ result) {
				if(result->Status != AudioGraphCreationStatus::Success){
					switch (result->Status) {
					case AudioGraphCreationStatus::DeviceNotAvailable:

						break;
					}
					return;
				}

				this->aGraph = result->Graph;
				
				concurrency::create_task(aGraph->CreateFileInputNodeAsync(AudioFile)).then(
					[this](CreateAudioFileInputNodeResult^ node_result) {
					auto a = node_result->Status;
						switch (node_result->Status) {
						case AudioFileNodeCreationStatus::Success:
							fileNode = node_result->FileInputNode;
							return aGraph->CreateDeviceOutputNodeAsync();

						case AudioFileNodeCreationStatus::InvalidFileType:

						case AudioFileNodeCreationStatus::FormatNotSupported:

						case AudioFileNodeCreationStatus::FileNotFound:

						case AudioFileNodeCreationStatus::UnknownFailure:
							concurrency::cancel_current_task();
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
						fileNode->AddOutgoingConnection(outputNode);
					}
				);
			} //lambda end;
		); //create_task end;
	} // fucntion end;


	concurrency::task<void> initGraph() {
		AudioGraphSettings^ graph_setting = ref new AudioGraphSettings(AudioRenderCategory::Media);
		graph_setting->QuantumSizeSelectionMode = QuantumSizeSelectionMode::LowestLatency;
		graph_setting->PrimaryRenderDevice = Out_Dev_info;


		return concurrency::create_task(AudioGraph::CreateAsync(graph_setting)).then(
			[this](CreateAudioGraphResult^ result) {
			if (result->Status != AudioGraphCreationStatus::Success) {
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
		); //create_task end;
	} // fucntion end;

};