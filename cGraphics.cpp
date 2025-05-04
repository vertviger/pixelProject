#include "cGraphics.h"
#include <map>
#include <SFML/Graphics/Texture.hpp>

class cTextures
{
public:
	const sf::Texture& Get(const std::string& _name)
	{
		auto itemIt = textureMap.find(_name);
		if (itemIt != textureMap.end()) return itemIt->second;
		textureMap[_name] = sf::Texture(_name);
		return textureMap[_name];
	}
private:
	std::map<std::string, sf::Texture> textureMap;
};

static cTextures textures;

const sf::Texture& GetTexture(const std::string& path)
{
	return textures.Get(path);
}