#include "cGraphics.h"
#include <map>
#include <SFML/Graphics/Texture.hpp>

static class cTextures
{
public:	
	const sf::Texture& Get(const std::string& _name)
	{
		auto it = items.find(_name);
		if(it != items.end()) return it->second;
		items[_name] = sf::Texture(_name);
		return items[_name];
	}
private:
	std::map<std::string, sf::Texture> items;
}textures;

const sf::Texture& GetTexture(const std::string& _n)
{
	return textures.Get(_n);
}