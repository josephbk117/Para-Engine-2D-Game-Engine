#include "ResourceManager.h"
#include <filesystem>

ResourceManager ResourceManager::instance;
ResourceManager::ResourceManager()
{
}
ResourceManager::~ResourceManager()
{
}

void ResourceManager::addResource(ResourceType resourceType, const std::string & filePath)
{
	if (resourceType == ResourceType::TEXTURE)
	{
		unsigned int fileSize = 0;
		try { fileSize = std::experimental::filesystem::file_size(filePath); }
		catch (std::experimental::filesystem::filesystem_error& e) {}
		ResourceFileData<Texture> textureData;
		textureData.data = new Texture(TextureManager::getImageDataAsTexture(filePath));
		textureData.fileSize = fileSize;
		textureResource.push_back(std::make_pair(filePath, textureData));
	}
}

const std::vector<std::pair<std::string, ResourceFileData<Texture>>>* ResourceManager::getTextureVector()
{
	return &textureResource;
}
