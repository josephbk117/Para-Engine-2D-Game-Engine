#pragma once
#include <unordered_map>
#include "SoundSource.h"
class AudioManager
{
public:
	AudioManager() = delete;
	AudioManager(const AudioManager&) = delete;
	static SoundSource* const loadAudioFromFile(const std::string& path, const std::string& referenceName);
	static SoundSource* const getAudioFromReference(const std::string& referenceName);
	static void removeAudio(const std::string& referenceName);
	static void removeLoadedAudioFromMemory();
private:
	static std::unordered_map<std::string, SoundSource *> audioUoMap;
};