#pragma once
#include "Scene.h"
#include "GameOverOptions.h"
#include "MenuFunctionality.h"

namespace SnakeGame {
    namespace Scene {
        class SceneGameOver :
            public Interface::Scene
        {
        private:
            // Resources
            sf::Font font;

            float timeSinceGameOver = 0.f;

            // UI data
            sf::RectangleShape background;
            sf::Text gameOverText;
            sf::Text hintText;
            std::vector<sf::Text> recordsTableTexts;

            std::vector<std::string> menu = {
                "Start Game",
                "Main menu"
            };
            std::vector<sf::Text> _menuOptions;
            MenuFunctionality<GameOverOptions> _menuFunc {};

        public:
            //static std::string PLAYER_NAME;
            SceneGameOver();
            // Унаследовано через Scene
            SceneCommand handleInput(sf::Event& event, float dt) override;
            SceneCommand update(float dt) override;
            void draw(sf::RenderWindow& window) override;
        };
    }
}

