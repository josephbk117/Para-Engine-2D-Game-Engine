#include "AudioManager.h"
#include <iostream>

std::unordered_map<std::string, SoundSource *> AudioManager::audioUoMap;
SoundSource* const AudioManager::loadAudioFromFile(const std::string & path, const std::string & referenceName)
{
	SoundSource* sData = new SoundSource(path);
	audioUoMap[referenceName] = sData;
	return sData;
}

SoundSource* const AudioManager::getAudioFromReference(const std::string & referenceName)
{
#if _DEBUG
	if (audioUoMap.find(referenceName) == audioUoMap.end())
		throw ("No Such Audio Was Loaded");
#endif
	return audioUoMap[referenceName];
}

void AudioManager::removeAudio(const std::string & referenceName)
{
	delete audioUoMap[referenceName];
	audioUoMap.erase(referenceName);
}

void AudioManager::removeLoadedAudioFromMemory()
{
	for (auto& x : audioUoMap)
		delete x.second;
	audioUoMap.erase(audioUoMap.begin(), audioUoMap.end());
}
