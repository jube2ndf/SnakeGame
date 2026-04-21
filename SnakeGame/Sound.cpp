#include "Sound.h"
#include <string>
#include <cassert>
#include <map>


SnakeGame::Sound::SoundObject::SoundObject(std::string file)
{
	this->soundFilePath = file;
	assert(this->buffer.loadFromFile(file));
	//if (!this->buffer.loadFromFile(file))
	//	throw std::runtime_error::runtime_error("Error load file" + file);
	this->player.setBuffer(this->buffer);
}

void SnakeGame::Sound::SoundObject::Play() const
{
    static std::vector<std::unique_ptr<sf::Sound>> activeSounds;
    static std::map<std::string, std::shared_ptr<sf::SoundBuffer>> bufferCache;
    auto sound = std::make_unique<sf::Sound>();

    if (bufferCache.find(this->soundFilePath) == bufferCache.end())
    {
        auto buffer = std::make_shared<sf::SoundBuffer>();
        if (!buffer->loadFromFile(this->soundFilePath))
            return;
        bufferCache[this->soundFilePath] = buffer;
    }

    sound->setBuffer(*bufferCache[this->soundFilePath]);
    sound->play();

    activeSounds.push_back(std::move(sound));

    activeSounds.erase(
        std::remove_if(activeSounds.begin(), activeSounds.end(),
            [](const auto& s) { return s->getStatus() == sf::Sound::Stopped; }),
        activeSounds.end()
    );
}

bool SnakeGame::Sound::SoundObject::IsFinished()
{
    return this->player.getStatus() == sf::Sound::Stopped;
}
