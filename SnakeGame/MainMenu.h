#pragma once
#include <SFML/Graphics.hpp>
#include "MainMenuOptions.h"
#include "MenuFunctionality.h"
#include "Settings.h"
#include "Scene.h"
#include "SceneCommand.h"
#include <iostream>
namespace SnakeGame {
	namespace Menu {
		class MainMenu: public Interface::Scene
		{
		private:
			sf::Font _font;
			sf::Text _gameName;

			const std::vector<std::string> _textMenuOptions = {
				"Start game", 
				"Complexity", 
				"Settings", 
				"Records", 
				"Exit"
			};
			
			std::vector<sf::Text> _menuOptions;

			MenuFunctionality<MainMenuOptions> _inputMenu{};


		public:
			MainMenu();

			SnakeGame::SceneCommand handleInput(sf::Event& event, float dt) override;
			SnakeGame::SceneCommand update(float dt) override;
			void draw(sf::RenderWindow& window) override;
		};
	}
}

