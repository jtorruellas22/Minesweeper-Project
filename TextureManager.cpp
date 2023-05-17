#include "TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName)
{
	string path = "images/";
	path += fileName + ".png";
	textures[fileName].loadFromFile(path);
}

const sf::Texture& TextureManager::GetTexture(string textureName)
{
	if (textures.find(textureName) == textures.end()) 
		LoadTexture(textureName);

	return textures[textureName];
}

void TextureManager::Clear()
{
	textures.clear();
}
