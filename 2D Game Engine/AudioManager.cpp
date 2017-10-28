#include "AudioManager.h"

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
