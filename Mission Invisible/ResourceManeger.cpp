#include "ResourceManeger.h"

ResourceManeger & ResourceManeger::getInstance()
{
	static ResourceManeger Resorces; // make singleton

	return Resorces;
}

const sf::Texture & ResourceManeger::getTexture(const std::string & type) const
{
	auto textureFileName = m_textureFilePos.find(type); // look for the textrue file name

	if (textureFileName == m_textureFilePos.end()) // case didn't find the object
		throw std::runtime_error("texture name not  found: " + type);

	auto texture = m_texture.find(textureFileName->second); // get the texture from the name

	if (texture == m_texture.end()) // case didn't find the object
		throw std::runtime_error("texture  file not found: " + textureFileName->second);

	return texture->second; // return the texture

}

sf::IntRect ResourceManeger::getTexturePos(const std::string &type) const
{
	auto texturePos = m_textureseRect.find(type);

	if (texturePos == m_textureseRect.end()) // case didn't find the object
		throw std::runtime_error("texture pos not found: " + type);

	return texturePos->second; // return the texture pos

}



const sf::Font & ResourceManeger::getFont() const
{
	return font;
}

sf::Sound & ResourceManeger::getSound(const SOUNDS & sound)
{
	return m_playSound[sound];
}



void ResourceManeger::sendErrorBox(std::string errorTitle, std::string errorMsg)
{
	std::wstring titleTemp = std::wstring(errorTitle.begin(), errorTitle.end());
	std::wstring msgTemp = std::wstring(errorMsg.begin(), errorMsg.end());
	LPCWSTR titleSTR = titleTemp.c_str();
	LPCWSTR errorSTR = msgTemp.c_str();

	MessageBox(0, errorSTR, titleSTR, MB_OK);
}

ResourceManeger::~ResourceManeger()
{
	m_texture.clear(); // to fix error when exit
}

ResourceManeger::ResourceManeger()
{
	textureLoad(); // load texture

	if (!font.loadFromFile(FONT_FILE))
	{
		std::string error = "Failed to load font file: " + FONT_FILE;
		sendErrorBox("file not found", error);
		exit(EXIT_FAILURE);
	}

	loadSound(); // load the sound

}


void ResourceManeger::textureLoad()
{
	std::ifstream inputFile(TEXTURE_DATA_FILE); // open the texture pos file

	if (!inputFile.is_open())
		throw(std::runtime_error("can't open texture pos"));

	while (!inputFile.eof())
	{
		std::string textueFileName; 
		getline(inputFile, textueFileName);


		sf::Texture currTexture; // to load the texture

		if (!currTexture.loadFromFile(textueFileName)) // case fail to load texture
		{
			std::string error = "Failed to load textrue file: " + textueFileName;
			sendErrorBox("file not found", error);
				exit(EXIT_FAILURE);
		}

		m_texture.emplace(textueFileName,std::move(currTexture)); // add the texture

		std::string currLine; // to get the currLine
		getline(inputFile, currLine);

		for (int lineNum = 0; !currLine.empty() && !inputFile.eof() ;
						lineNum++, getline(inputFile, currLine)) // get line until got to empty of eof
		{
			std::stringstream ss(currLine); // the read item item from the line
			int colNum = 0; // the currCol
			std::string currItem; // the curritem that add texture to

			while (!ss.eof())
			{
				ss >> currItem; // get the item
				m_textureFilePos.emplace(currItem, textueFileName); // the item is with this file
				sf::IntRect posIntexutre(sf::Vector2i(colNum*TILESIZE, lineNum*TILESIZE), sf::Vector2i(TILESIZE, TILESIZE));
				m_textureseRect.emplace(currItem, posIntexutre); // add the item pos in the texture
				++colNum;
			}
		}
	}


}

void ResourceManeger::loadSound()
{
	//enum SOUNDS {  ARROW_SD, LOST_LIFE_SD, END_LEVEL_SD, PICK_ITEM_SD,DEAD_SD };


	m_sounds.emplace_back(openSoundFile("sounds/arrow.ogg"));
	m_sounds.emplace_back(openSoundFile("sounds/lost_life.ogg"));
	m_sounds.emplace_back(openSoundFile("sounds/end_level.ogg"));
	m_sounds.emplace_back(openSoundFile("sounds/pick_item.ogg"));
	m_sounds.emplace_back(openSoundFile("sounds/dead.ogg"));

	for (auto &x : m_sounds)
		m_playSound.push_back(sf::Sound(x));

}

sf::SoundBuffer ResourceManeger::openSoundFile(const std::string & soundfile)
{
	sf::SoundBuffer temp;

	if (!temp.loadFromFile(soundfile))
	{
		std::string error = "Failed to load font file: " + soundfile;
		sendErrorBox("file not found", error);
		exit(EXIT_FAILURE);
	}

	return std::move(temp);
}
