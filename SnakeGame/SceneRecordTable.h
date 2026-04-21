#pragma once
#include "Scene.h"
#include "SceneCommand.h"

namespace SnakeGame {
	namespace Scene {
		class SceneRecordTable : public Interface::Scene
		{
		private:
			sf::Font _font;
			sf::Text _sceneName;
			std::vector<sf::Text> _top;
		public:
			SceneRecordTable();
			// Унаследовано через Scene
			SceneCommand handleInput(sf::Event& event, float dt) override;
			SceneCommand update(float dt) override;
			void draw(sf::RenderWindow& window) override;
		};
	}
}


