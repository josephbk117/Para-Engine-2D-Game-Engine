#pragma once
#include <Yse\yse.hpp>
#include <unordered_map>
class AudioManager
{
public:
	static YSE::sound* loadAudioFromFile(const std::string& path, const std::string& referenceString);
	static YSE::sound* getAudioFromReference(const std::string& referenceString);
private:
	static std::unordered_map<std::string, YSE::sound *> audioUoMap;
};