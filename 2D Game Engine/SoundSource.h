#pragma once
#include <string>
class SoundSource
{
public:
	SoundSource(const std::string& path);
	void play();
	void stop();
	void pause();
	bool isPaused();
	bool isPlaying();
	void setLooping(bool canLoop);
	bool isLooping();
	void setVolume(float volume, unsigned int timeInMillis = 0);
	float getVolume();
	~SoundSource();
private:
	struct internalAcess;
	internalAcess* access;
};

