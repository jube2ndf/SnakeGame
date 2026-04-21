#pragma once
#include <SFML/Graphics.hpp>

namespace SnakeGame {
	namespace Models {
		using namespace sf;

		class GameObject
		{
			protected:
				std::shared_ptr<sf::Texture> _objectTexture = nullptr;
				Sprite _objectSprite;

				void LoadTexture(std::string file);
			public:
				GameObject(std::string file);
				GameObject(std::string file, int spriteSize);
				GameObject(std::string file, int spriteSize, Vector2f position);
				GameObject(std::string file, int spriteSize, Vector2f position, float rotation);

				void setPosition(Vector2f newPosition);
				void setRotation(float rotation);
				void DrawObject(RenderWindow& win);
		};
	}
}

