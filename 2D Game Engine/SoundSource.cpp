#include "SoundSource.h"
#include <Yse\yse.hpp>

struct SoundSource::internalAcess
{
	YSE::sound* sData = nullptr;
};

SoundSource::SoundSource(const std::string& path)
{
	access = new internalAcess();
	access->sData = new YSE::sound();
	access->sData->create(path.c_str());
}

void SoundSource::play()
{
	access->sData->play();
}

void SoundSource::stop()
{
	access->sData->stop();
}

void SoundSource::pause()
{
	access->sData->pause();
}

bool SoundSource::isPaused()
{
	return access->sData->isPaused();
}

bool SoundSource::isPlaying()
{
	return access->sData->isPlaying();
}

void SoundSource::setLooping(bool canLoop)
{
	access->sData->setLooping(canLoop);
}

bool SoundSource::isLooping()
{
	return access->sData->isLooping();
}

void SoundSource::setVolume(float volume, unsigned int timeInMillisec)
{
	access->sData->setVolume(volume, timeInMillisec);
}

float SoundSource::getVolume()
{
	return access->sData->getVolume();
}

SoundSource::~SoundSource()
{
	delete access->sData;
}
