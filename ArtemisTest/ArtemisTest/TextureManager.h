

#ifndef __TEXTUREMANAGER_H
#define __TEXTUREMANAGER_H

#include <map>

#include "SFML/Graphics.hpp"

class TextureManager
{
public:
	static sf::Texture& GetTexture(const std::string& path);

private:
	typedef std::map<std::string, sf::Texture>::iterator textureIterator;
	static std::map<std::string, sf::Texture> textures;
};

#endif