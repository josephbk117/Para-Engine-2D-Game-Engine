#pragma once
#include <TextureLoader.h>
#include <Texture.h>
#include <vector>
#include <utility>

enum class ResourceType
{
	TEXTURE, AUDIO, SCRIPTS
};

template <typename T>
struct ResourceFileData
{
	ResourceFileData()
	{
		data = nullptr;
		fileSize = 0;
	}
	T* data;
	unsigned int fileSize;
};

class ResourceManager
{
public:
	static ResourceManager instance;
	void addResource(ResourceType resourceType, const std::string& filePath);
	const std::vector<std::pair<std::string, ResourceFileData<Texture>>> * getTextureVector();
	ResourceManager();
	~ResourceManager();
private:
	std::vector<std::pair<std::string, ResourceFileData<Texture>>> textureResource;
};

