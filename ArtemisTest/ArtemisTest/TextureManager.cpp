
#include "TextureManager.h"

std::map<std::string, sf::Texture> TextureManager::textures;

sf::Texture& TextureManager::GetTexture(const std::string& path)
{
	textureIterator iter = textures.find(path);
	if(iter != textures.end()) {
		return iter->second;
	} else {
		textures[path] = sf::Texture();
		textures[path].loadFromFile(path);
		return textures[path];
	}
}