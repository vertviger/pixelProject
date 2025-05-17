#pragma once
#include <SFML/Graphics.hpp>

const std::string& AssetsPath();
const sf::Texture& GetTexture(const std::string& _file_name);
const sf::Font& GetFont();
