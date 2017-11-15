#pragma once
#include <unordered_map>
#include "SoundSource.h"
class AudioManager
{
public:
	static SoundSource* const loadAudioFromFile(const std::string& path, const std::string& referenceString);
	static SoundSource* const getAudioFromReference(const std::string& referenceString);
	static void removeLoadedAudioFromMemory();
private:
	static std::unordered_map<std::string, SoundSource *> audioUoMap;
	AudioManager() {}
};