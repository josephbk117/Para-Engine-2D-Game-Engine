#include "ResourceManager.h"
#include <filesystem>

ResourceManager ResourceManager::instance;
ResourceManager::ResourceManager()
{
}
ResourceManager::~ResourceManager()
{
	for (int i = 0; i < imageResource.size(); i++)
		delete std::get<1>(imageResource[i]).data;
}

void ResourceManager::addResource(ResourceType resourceType, const std::string & filePath)
{
	if (resourceType == ResourceType::TEXTURE)
	{
		unsigned int fileSize = 0;
		try { fileSize = std::experimental::filesystem::file_size(filePath); }
		catch (std::experimental::filesystem::filesystem_error& e) {}
		ResourceFileData<glm::vec2> imageData;
		imageData.data = new glm::vec2(TextureManager::getImageDimensions(filePath));
		imageData.fileSize = fileSize;
		imageResource.push_back(std::make_pair(filePath, imageData));
	}
}

const std::vector<std::pair<std::string, ResourceFileData<glm::vec2>>>* ResourceManager::getImageVector()
{
	return &imageResource;
}
