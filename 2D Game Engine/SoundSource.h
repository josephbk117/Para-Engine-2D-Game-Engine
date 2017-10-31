#pragma once
#include <memory>
#include <string>
class SoundSource
{
public:
	SoundSource(const std::string& path);
	void play();
	~SoundSource();
private:
	struct internalAcess;
	internalAcess* acess;
};

