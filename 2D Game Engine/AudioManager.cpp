#include "AudioManager.h"
#include <iostream>

std::unordered_map<std::string, SoundSource *> AudioManager::audioUoMap;
SoundSource* AudioManager::loadAudioFromFile(const std::string & path, const std::string & referenceString)
{
	SoundSource* sData = new SoundSource(path);
	audioUoMap[referenceString] = sData;
	return sData;
}

SoundSource* AudioManager::getAudioFromReference(const std::string & referenceString)
{
	return audioUoMap[referenceString];
}

void AudioManager::removeLoadedAudioFromMemory()
{
	for (auto& x : audioUoMap)
	{
		delete x.second;
	}
	audioUoMap.erase(audioUoMap.begin(), audioUoMap.end());
}
