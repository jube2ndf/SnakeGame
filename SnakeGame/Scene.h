#pragma once
#include <SFML/Graphics.hpp>
#include "SceneCommand.h"
namespace SnakeGame {
    namespace Interface {
        class Scene {
        public:
            virtual ~Scene() = default;
            virtual SceneCommand handleInput(sf::Event& event, float dt) = 0;
            virtual SceneCommand update(float dt) = 0;
            virtual void draw(sf::RenderWindow& window) = 0;

            virtual void pause() {}   // Вызывается, когда сверху кладут новое состояние
            virtual void resume() {}  // Вызывается, когда верхнее состояние удалили
        };
    }
}