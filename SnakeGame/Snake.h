#pragma once
#include <SFML/Graphics.hpp>
#include "GameSprite.h"
#include <array>
#include <list>
namespace SnakeGame
{
	namespace Game
	{
		namespace GameObject
		{
			enum class SnakeDirection
			{
				Up = 0,
				Right,
				Down,
				Left
			};

			enum class SnakePart : uint8_t
			{
				Head = 0,
				Body,
				BodyBend,
				Tail,
				Count
			};

			class Snake
			{
			private:
				std::list<SnakeGame::Game::GameObject::GameSprite> body;
				std::list<SnakeGame::Game::GameObject::GameSprite>::iterator head;
				std::list<SnakeGame::Game::GameObject::GameSprite>::iterator tail;
				float speed = 0.f;
				
				SnakeDirection direction = SnakeDirection::Up;
				SnakeDirection prevDirection = SnakeDirection::Up;
				SnakeDirection nextDirection = SnakeDirection::Up;
				std::array<sf::Texture, (size_t)SnakePart::Count> textures;
				sf::Vector2f getVectorDirection();
				void SetHead(std::list<SnakeGame::Game::GameObject::GameSprite>::iterator it);
				void GetRotationSprite(std::list<GameObject::GameSprite>::iterator it);
				void SetTailSprite(std::list<SnakeGame::Game::GameObject::GameSprite>::iterator it);

				sf::Vector2i gridPos;
				sf::Vector2f targetPosition;
			public:
				Snake();
				Snake(float startSpeed);
				void GrowSnake();
				std::list<SnakeGame::Game::GameObject::GameSprite>::iterator GetNextIterator(std::list<SnakeGame::Game::GameObject::GameSprite>::iterator it);
				std::list<SnakeGame::Game::GameObject::GameSprite>::iterator GetPrevIterator(std::list<SnakeGame::Game::GameObject::GameSprite>::iterator it);
				bool CheckHeadIntersection(const SnakeGame::Game::GameObject::GameSprite& sprite);
				bool FullCheckCollisions(std::list<SnakeGame::Game::GameObject::GameSprite>::iterator first, std::list<SnakeGame::Game::GameObject::GameSprite>::iterator last);
				void SetDirection(SnakeDirection newSnakeDirection);
				void Draw(sf::RenderWindow& windiw);
				const std::list<SnakeGame::Game::GameObject::GameSprite> getBody();
				void Move(float df, const sf::FloatRect& bounds);
				bool HasSnakeCollisionWithRect(const sf::FloatRect& rect);
				bool CheckSnakeCollisionWithHimself();
				void SnapToGrid(const sf::FloatRect& bounds);
				bool IsHeadInCellCenter(const sf::FloatRect& bounds);
				void AddSpead(float value);
			};
		}
	}
}