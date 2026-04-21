#pragma once
#include "Scene.h"
#include "Snake.h"
#include "SFML/Audio.hpp"
#include "Settings.h"
#include "Sound.h"

namespace SnakeGame {
	namespace Scene {
		class ScenePlay :
			public Interface::Scene
		{
		protected:
			// Resources
			sf::Texture appleTexture;
			sf::Texture rockTexture;
			sf::Font font;

			// Game data
			Game::GameObject::Snake snake;
			Game::GameObject::GameSprite apple;
			std::list<Game::GameObject::GameSprite> rocks;
			int numEatenApples = 0;
			float elapsedTime = 0.f;

			// UI data
			sf::Text scoreText;
			sf::Text inputHintText;
			sf::RectangleShape background;
			sf::FloatRect bounds;
			int cols;
			int rows;

			// Sounds
			Sound::SoundObject eat;
			Sound::SoundObject death;

		public:

			ScenePlay();

			// Унаследовано через Scene
			SceneCommand handleInput(sf::Event& event, float dt) override;
			SceneCommand update(float dt) override;
			void draw(sf::RenderWindow& window) override;

		};
	}
}

