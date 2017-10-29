#include "AudioManager.h"
#include <iostream>

std::unordered_map<std::string, YSE::sound *> AudioManager::audioUoMap;
YSE::sound* AudioManager::loadAudioFromFile(const std::string & path, const std::string & referenceString)
{
	YSE::sound* sData = new YSE::sound();
	sData->create(path.c_str());
	audioUoMap[referenceString] = sData;
	return sData;
}

YSE::sound* AudioManager::getAudioFromReference(const std::string & referenceString)
{
	return audioUoMap[referenceString];
}

void AudioManager::removeLoadedAudioFromMemory()
{
	for (auto& x : audioUoMap)
	{
		std::cout <<"\nDeleted "<< x.first << ": " << x.second << std::endl;
		delete x.second;
	}
	audioUoMap.erase(audioUoMap.begin(), audioUoMap.end());
}
