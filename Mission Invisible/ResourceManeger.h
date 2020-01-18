#pragma once

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h> // for errors
#include <random>
#include <map>
#include <utility>
#include <fstream>
#include <sstream>
#include "Const.h"

/*
used to load resources for the game Font\Music\Texture
*/

class ResourceManeger
{
public:
	// return the instance of the singleton of Resources
	static ResourceManeger& getInstance();

	// return the texture that load for the game
	const sf::Texture& getTexture(const std::string &type) const;
	sf::IntRect getTexturePos(const std::string &type) const; // return the textrue pos on hte file


	// return the font that load for the game
	const sf::Font& getFont() const;

	sf::Sound & getSound(const SOUNDS& sound);

	// send to the user error msg  errorTitle to box title errorMsg the bos msg
	void sendErrorBox(std::string errorTitle, std::string errorMsg);

	// copy constructors and assigns operator isn't need
	// to stop user copy the singleton
	ResourceManeger(const ResourceManeger&) = delete;
	ResourceManeger& operator=(const ResourceManeger&) = delete;

	~ResourceManeger();

private:
	sf::Font font; // the game font

	ResourceManeger(); // constructor


	std::map<std::string, std::string> m_textureFilePos; // witch file the texture is
	std::map<std::string, sf::Texture> m_texture; // the texture file
	std::map<std::string, sf::IntRect> m_textureseRect; // the part to load the texture

	std::vector<sf::SoundBuffer> m_sounds;
	std::vector<sf::Sound> m_playSound;


	void textureLoad(); // load the texture as from file
	void loadSound();

	sf::SoundBuffer openSoundFile(const std::string & soundfile);
};