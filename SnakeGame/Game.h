#pragma once
#include <vector>
#include <memory>
#include "Scene.h"

namespace SnakeGame{
    class Game {

        sf::RenderWindow window;
        std::vector<std::unique_ptr<Interface::Scene>> scenes;

    public:
        Game();

        void pushScene(std::unique_ptr<Interface::Scene> scene);

        void popScene();

        void run();
        
    };
}

