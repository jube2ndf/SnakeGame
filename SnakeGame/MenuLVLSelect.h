#pragma once
#include <SFML/Graphics.hpp>
#include "MenuFunctionality.h"
#include "MainMenuOptions.h"
#include "SceneLVLComplexityOptions.h"
#include "Scene.h"

namespace SnakeGame {
	namespace Menu {
		class MenuLVLSelect : public Interface::Scene
		{
		private:
			sf::Font _font;
			sf::Text _sceneName;

			const std::vector<std::string> _textMenuOptions = {
				"Easy",
				"More difficult than easy",
				"Medium",
				"Easier than difficult",
				"Difficult",
			};

			std::vector<sf::Text> _menuOptions;

			MenuFunctionality<SceneLVLComplecityOptions> _inputMenu;
		public:
			MenuLVLSelect();
			// Унаследовано через Scene
			SceneCommand handleInput(sf::Event& event, float dt) override;
			SceneCommand update(float dt) override;
			void draw(sf::RenderWindow& window) override;
		};
	}
}


