#pragma once
#include "Scene.h"
namespace SnakeGame {
    namespace Scene {
        class SceneEnterName :
            public Interface::Scene
        {
        private:
            sf::Font _font;

            sf::Text _enterName;

            sf::String _drawingString; // Создаём строку с вводимым текстом
            sf::Text _text;
            
        public:
            SceneEnterName();

            // Унаследовано через Scene
            SceneCommand handleInput(sf::Event& event, float dt) override;

            SceneCommand update(float dt) override;

            void draw(sf::RenderWindow& window) override;

        };
    }
}

