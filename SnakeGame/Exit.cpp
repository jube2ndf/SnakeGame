#include "Exit.h"

SnakeGame::SceneCommand SnakeGame::Scene::Exit::handlersQuestionYesNo(QuestionYesNo& cmd)
{
	switch (cmd)
	{
	case QuestionYesNo::Back:
		return SceneCommand(GameSceneRequest::Pop);
	case QuestionYesNo::Yes:
		return SceneCommand(GameSceneRequest::Clear);
	case QuestionYesNo::No:
		return SceneCommand(GameSceneRequest::Pop);
	default:
		break;
	}
    return SceneCommand(GameSceneRequest::None);
}

SnakeGame::Scene::Exit::Exit():
	SceneQuestionYesNo("Leave the game?")
{

}
