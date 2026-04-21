#pragma once
#include <SFML/Audio.hpp>
#include <string>

namespace SnakeGame {
	namespace Sound {
		class SoundObject
		{
		protected:
			std::string soundFilePath;
			sf::SoundBuffer buffer;
			sf::Sound player;
		public:
			SoundObject(std::string file);
			SoundObject() {};
			void Play() const;
			bool IsFinished();
		};
	}
}


