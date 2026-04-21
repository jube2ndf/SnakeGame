#pragma once
#include "GameSceneRequest.h"
#include "GameStateType.h"
namespace SnakeGame {
    struct SceneCommand
    {
        GameSceneRequest action;
        GameSceneType id;
        SceneCommand(GameSceneRequest action)
            : action(action), id(GameSceneType::None) {
        }

        SceneCommand(GameSceneRequest action, GameSceneType id)
            : action(action), id(id) {
        }
    };
}