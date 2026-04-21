#pragma once
#include <SFML/Graphics.hpp>
#include <list>

namespace SnakeGame
{
	namespace Game 
	{
		namespace GameObject 
		{
			class GameSprite
			{
			private:
				sf::Sprite sprite;
			public:
				GameSprite();
				GameSprite(float desiredWidth,
					float desiredHeight,
					const sf::Texture& texture);
				void Draw(sf::RenderWindow& window);
				void SetOrigin(float originX, float originY);
				void SetSize(float newWidth, float newHeight);
				void SetRandomPosition(const sf::FloatRect& rect, const std::list<GameSprite>& collection);
				bool CheckSpriteIntersection(const GameSprite& sprite2);
				void SetRandomSpritePositionInRectangle(const sf::FloatRect& rect);
				void SetPosition(sf::Vector2f v);
				sf::Vector2f getPosition();
				void setTexture(const sf::Texture& texture);
				void setRotation(const float angel);
				const sf::Sprite& GetSprite();
				sf::Vector2f GetVectorBetweenSprites(const GameSprite& spriteTo);
				float GetManhattanDistanceBetweenSprites(const GameSprite& spriteTo);

				template<typename Iterator>
				bool FullCheckCollisions(Iterator first, Iterator last){
					for (; first != last; ++first) {
						if (&(*first) == this)
							continue;
						if (this->CheckSpriteIntersection(*first)) {
							return true;
						}
					}
					return false;
				}
			};
		}
	}
}
