#pragma once
#include <TextureLoader.h>
#include <Texture.h>
#include <vector>
#include <utility>
#include <unordered_map>
#include <GLM\common.hpp>

enum class ResourceType
{
	TEXTURE, AUDIO, SCRIPTS
};

template <typename T, typename K>
struct ResourceFileData
{
	ResourceFileData()
	{
		data1 = nullptr;
		fileSize = 0;
	}
	T* data1;
	K* data2;
	unsigned int fileSize;
};

class ResourceManager
{
public:
	static ResourceManager instance;
	void addResource(ResourceType resourceType, const std::string& filePath, const std::string reference);
	const std::vector<std::pair<std::string, ResourceFileData<glm::vec2, unsigned int>>> * getImageVector();
	ResourceManager();
	~ResourceManager();
private:
	std::vector<std::pair<std::string, ResourceFileData<glm::vec2, unsigned int>>> imageResource;
};

