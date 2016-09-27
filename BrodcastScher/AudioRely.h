#pragma once

#include "pch.h"

using namespace Windows::Media::MediaProperties;
using namespace Windows::Media::Devices;
using namespace Windows::Media::Audio;
using namespace Windows::Media::Render;
using namespace Windows::Media::Capture;
using namespace Windows::Media::Playlists;

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
			CreateEqEffect();
			CreateLimiterEffect();

			if (start_after_finish)
				StartStreaming(); 
		});
	}


	AudioRely(std::wstring inputfile_path, int device_index_o, bool start_after_finish, bool isPlaylist) {
		// Get Input/output DeiveceInfo by Index;
		auto init_task = concurrency::create_task(DeviceInformation::FindAllAsync(MediaDevice::GetAudioRenderSelector())).then(
			[this, device_index_o, inputfile_path](concurrency::task<DeviceInformationCollection^> task) {
			auto devices = task.get();

			if (devices->Size > device_index_o)
				Out_Dev_info = devices->GetAt(device_index_o);

			return StorageFile::GetFileFromPathAsync(ref new Platform::String(inputfile_path.c_str()));
		})
		.then([this, isPlaylist](concurrency::task<StorageFile^> taskF) {
			try {
				if(!isPlaylist)
					AudioFile = taskF.get();
				else {
					concurrency::create_task(Playlist::LoadAsync(taskF.get())).then([this](Playlist^ list) {
						AudioPlaylist = list;
						// Get and check playlist file.
						if (AudioPlaylist->Files->Size > 0)
							AudioFile = AudioPlaylist->Files->GetAt(0);
						else
							concurrency::cancel_current_task();
					}).wait();
				}
				
			}
			catch (Platform::COMException^ e) {
				auto debug = e->Message;
				concurrency::cancel_current_task(); 
			}
		})
		.then([this, isPlaylist]() { 
			if (!isPlaylist)
				initGraphWithFile().wait();
			else
				initGraphWithPlayList().wait();
		})
		.then([this, start_after_finish]() {
			CreateEqEffect();
			CreateLimiterEffect();

			if (start_after_finish)
				StartStreaming();
		});
	}

	~AudioRely() {
		
		aGraph = nullptr;
		inputNode = nullptr;
		outputNode = nullptr;
		fileNode = nullptr;
		AudioPlaylist = nullptr;
		AudioFile = nullptr;
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


	bool EnableEffects(int index) {
		if (EQeffect == nullptr || LimiterEffect == nullptr)
			return false;

		if (inputNode != nullptr) {
			switch (index) {
			case 1:
				inputNode->EnableEffectsByDefinition(LimiterEffect);
				break;
			case 2:
				inputNode->EnableEffectsByDefinition(EQeffect);
				break;
			}
		}

		if (fileNode != nullptr) {
			switch (index) {
			case 1:
				fileNode->EnableEffectsByDefinition(LimiterEffect);
				break;
			case 2:
				fileNode->EnableEffectsByDefinition(EQeffect);
				break;
			}
		}

		return true;
	}


	bool DisableEffects(int index) {
		if (EQeffect == nullptr || LimiterEffect == nullptr)
			return false;

		if (inputNode != nullptr) {
			switch (index) {
			case 1:
				inputNode->DisableEffectsByDefinition(LimiterEffect);
				break;
			case 2:
				inputNode->DisableEffectsByDefinition(EQeffect);
				break;
			}
		}

		if (fileNode != nullptr) {
			switch (index) {
			case 1:
				fileNode->DisableEffectsByDefinition(LimiterEffect);
				break;
			case 2:
				fileNode->DisableEffectsByDefinition(EQeffect);
				break;
			}
		}

		return true;
	}


	void SetEffectValue(unsigned int index, double value) {
		switch (index) {
		case 0: // EQ Bands_0
			if(EQeffect != nullptr)
				EQeffect->Bands->GetAt(0)->Gain = value;
			break;
		case 1: // EQ Bands_1
			if (EQeffect != nullptr)
				EQeffect->Bands->GetAt(1)->Gain = value;
			break;
		case 2: // EQ Bands_2
			if (EQeffect != nullptr)
				EQeffect->Bands->GetAt(2)->Gain = value;
			break;
		case 3: // EQ Bands_3
			if (EQeffect != nullptr)
				EQeffect->Bands->GetAt(3)->Gain = value;
			break;
		case 4: // Limiter Loudness
			if (LimiterEffect!= nullptr)
				LimiterEffect->Loudness = value;
			break;
		}
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
	Playlist^ AudioPlaylist;
	unsigned int PlaylistCounter = 0;

	EqualizerEffectDefinition^ EQeffect;
	LimiterEffectDefinition^ LimiterEffect;

	concurrency::task<void> initGraphWithPlayList() {
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

				auto addNewFile = [this](Windows::Media::Audio::AudioFileInputNode ^ fileInputNode, Platform::Object ^ sender) {
					GetPlaylistFile();
				};

				fileNode->FileCompleted += ref new Windows::Foundation::TypedEventHandler<Windows::Media::Audio::AudioFileInputNode ^, Platform::Object ^>(addNewFile);
			}
			).wait();
		} //lambda end;
		); //create_task end;
	} // fucntion end;


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
				).wait();
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
			).wait();
		}); //create_task end;
	} // fucntion end;


	void GetPlaylistFile() {

		++PlaylistCounter;
		if (PlaylistCounter >= AudioPlaylist->Files->Size) {
			AudioPlaylist = nullptr;
			return;
		}

		AudioFile = AudioPlaylist->Files->GetAt(PlaylistCounter);

		// Create new fileInputNode.
		concurrency::create_task(aGraph->CreateFileInputNodeAsync(AudioFile)).then(
			[this](CreateAudioFileInputNodeResult^ node_result) {
			auto a = node_result->Status;
			switch (node_result->Status) {
			case AudioFileNodeCreationStatus::Success:
				fileNode = node_result->FileInputNode;
				fileNode->AddOutgoingConnection(outputNode);

				// Registe FileCompleted Handler for next  file in audio playlist.
				fileNode->FileCompleted += ref new Windows::Foundation::TypedEventHandler<Windows::Media::Audio::AudioFileInputNode ^, Platform::Object ^>(
					[this](Windows::Media::Audio::AudioFileInputNode ^node, Platform::Object ^args) {
					GetPlaylistFile();
				});
				break;

			case AudioFileNodeCreationStatus::InvalidFileType:

			case AudioFileNodeCreationStatus::FormatNotSupported:

			case AudioFileNodeCreationStatus::FileNotFound:

			case AudioFileNodeCreationStatus::UnknownFailure:
				concurrency::cancel_current_task();
				break;
			}
		});
	
		
	} // GetPlaylistFile end.


	void CreateEqEffect() {
		EQeffect = ref new EqualizerEffectDefinition(aGraph);
		
		EQeffect->Bands->GetAt(0)->FrequencyCenter = 100.0;
		EQeffect->Bands->GetAt(0)->Gain = 4.033;
		EQeffect->Bands->GetAt(0)->Bandwidth = 1.5;

		EQeffect->Bands->GetAt(1)->FrequencyCenter = 900.0;
		EQeffect->Bands->GetAt(1)->Gain = 1.6888;
		EQeffect->Bands->GetAt(1)->Bandwidth = 1.5;

		EQeffect->Bands->GetAt(2)->FrequencyCenter = 5000.0;
		EQeffect->Bands->GetAt(2)->Gain = 2.4702;
		EQeffect->Bands->GetAt(2)->Bandwidth = 1.5;

		EQeffect->Bands->GetAt(3)->FrequencyCenter = 12000.0;
		EQeffect->Bands->GetAt(3)->Gain = 5.5958;
		EQeffect->Bands->GetAt(3)->Bandwidth = 2.0;

		if (inputNode != nullptr) {
			inputNode->EffectDefinitions->Append(EQeffect);
			inputNode->DisableEffectsByDefinition(EQeffect);
		}

		if (fileNode != nullptr) {
			fileNode->EffectDefinitions->Append(EQeffect);
			fileNode->DisableEffectsByDefinition(EQeffect);
		}
	}


	void CreateLimiterEffect() {
		LimiterEffect = ref new LimiterEffectDefinition(aGraph);
		LimiterEffect->Loudness = 1000;
		LimiterEffect->Release = 10;

		if (inputNode != nullptr) {
			inputNode->EffectDefinitions->Append(LimiterEffect);
			inputNode->DisableEffectsByDefinition(LimiterEffect);
		}

		if (fileNode != nullptr) {
			fileNode->EffectDefinitions->Append(LimiterEffect);
			fileNode->DisableEffectsByDefinition(LimiterEffect);
		}
	}

};