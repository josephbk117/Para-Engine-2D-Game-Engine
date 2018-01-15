#include "SoundSource.h"
#include "GLM\common.hpp"
#include <Yse\yse.hpp>

struct SoundSource::internalAcess
{
	YSE::sound* soundData = nullptr;
};

SoundSource::SoundSource(const std::string& path)
{
	access = new internalAcess();
	access->soundData = new YSE::sound();
	access->soundData->create(path.c_str());
}

void SoundSource::play()
{
	access->soundData->play();
}

void SoundSource::stop()
{
	access->soundData->stop();
}

void SoundSource::pause()
{
	access->soundData->pause();
}

void SoundSource::restart()
{
	access->soundData->restart();
}

void SoundSource::toggle()
{
	access->soundData->toggle();
}

bool SoundSource::isPaused() const
{
	return access->soundData->isPaused();
}

bool SoundSource::isPlaying() const
{
	return access->soundData->isPlaying();
}

void SoundSource::setLooping(bool canLoop)
{
	access->soundData->setLooping(canLoop);
}

bool SoundSource::isLooping() const
{
	return access->soundData->isLooping();
}

void SoundSource::setVolume(float volume, unsigned int timeInMillisec)
{
	volume = glm::clamp(volume, 0.0f, 1.0f);
	access->soundData->setVolume(volume, timeInMillisec);
}

float SoundSource::getVolume() const
{
	return access->soundData->getVolume();
}

void SoundSource::setSpeed(float speed)
{
	access->soundData->setSpeed(speed);
}

float SoundSource::getSpeed()
{
	return access->soundData->getSpeed();
}

unsigned int SoundSource::getLength() const
{
	return access->soundData->getLength();
}

float SoundSource::getTime() const
{
	return access->soundData->getTime();
}

SoundSource::~SoundSource()
{
	delete access->soundData;
}
