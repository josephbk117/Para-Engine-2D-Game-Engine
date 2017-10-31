#include "SoundSource.h"
#include <Yse\yse.hpp>

struct SoundSource::internalAcess
{
	YSE::sound* sData = nullptr;
};

SoundSource::SoundSource(const std::string& path)
{
	acess = new internalAcess();
	acess->sData = new YSE::sound();
	acess->sData->create(path.c_str());
}

void SoundSource::play()
{
	acess->sData->play();
}

void SoundSource::stop()
{
	acess->sData->stop();
}

SoundSource::~SoundSource()
{
	delete acess->sData;
}
