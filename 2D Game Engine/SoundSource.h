#pragma once
#include <string>
class SoundSource
{
public:
	SoundSource(const std::string& path);
	void play();
	void stop();
	void pause();
	void restart();
	void toggle();
	bool isPaused()const;
	bool isPlaying()const;
	void setLooping(bool canLoop);
	bool isLooping()const;
	void setVolume(float volume, unsigned int timeInMillis = 0);
	float getVolume()const;
	unsigned int getLength()const;
	float getTime()const;
	~SoundSource();
private:
	struct internalAcess;
	internalAcess* access;
};

