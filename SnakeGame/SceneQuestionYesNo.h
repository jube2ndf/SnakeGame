#pragma once
#include <SFML/Graphics.hpp>
#include "MenuFunctionality.h"
#include "QuestionYesNo.h"
#include "Scene.h"


namespace SnakeGame {
	namespace Scene {
		class SceneQuestionYesNo:
			public Interface::Scene
		{
		protected:

			sf::Font _font;
			sf::Text _question;

			const std::vector<std::string> _textMenuOptions = {
				"Yes",
				"No"
			};

			std::vector<sf::Text> _menuOptions;

			MenuFunctionality<QuestionYesNo> _inputMenu{};

		public:
			SceneQuestionYesNo(std::string question);

			virtual SceneCommand handlersQuestionYesNo(QuestionYesNo& cmd) = 0;

			// Унаследовано через Scene
			SceneCommand handleInput(sf::Event& event, float dt) override;

			SceneCommand update(float dt) override;

			void draw(sf::RenderWindow& window) override;

		};
		
	}
}

