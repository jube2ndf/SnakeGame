#pragma once
#include <functional>
#include <map>
#include <memory>
#include "GameStateType.h"
#include "MainMenu.h"

namespace SnakeGame::Interface
{
    class Scene; // forward declaration
}

namespace SnakeGame::Factory
{
    class SceneFactory
    {
    private:
        std::map<GameSceneType, std::function<std::unique_ptr<SnakeGame::Interface::Scene>()>> factorys;

    public:
        SceneFactory() {
            this->factorys = {};
        }

        SceneFactory(const SceneFactory&) = delete;
        SceneFactory& operator=(const SceneFactory&) = delete;
        template<typename T>
        void registrateScane(GameSceneType id)
        {
            
            factorys[id] = []()
                {
                    return std::make_unique<T>();
                };
                
        }

        std::unique_ptr<SnakeGame::Interface::Scene> create(GameSceneType stateID)
        {
            if(factorys.count(stateID) != 0)
                return factorys.at(stateID)();
            return nullptr;
        }
    };
}