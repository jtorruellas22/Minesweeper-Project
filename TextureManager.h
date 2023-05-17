#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <string>
using std::unordered_map;
using std::string;

class TextureManager
{
	static unordered_map<string, sf::Texture> textures;
	static void LoadTexture(string fileeName);
public:
	const static sf::Texture& GetTexture(string textureName);
	static void Clear();
};

