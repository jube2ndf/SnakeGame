#include "QuestionEnterName.h"

SnakeGame::Scene::QuestionEnterName::QuestionEnterName():
    SceneQuestionYesNo("Enter a name?")
{
}

SnakeGame::SceneCommand SnakeGame::Scene::QuestionEnterName::handlersQuestionYesNo(QuestionYesNo& cmd)
{
	switch (cmd)
	{
	case QuestionYesNo::Back:
		return SceneCommand(GameSceneRequest::Pop);
	case QuestionYesNo::Yes:
		return SceneCommand(GameSceneRequest::Push, GameSceneType::EnterName);
	case QuestionYesNo::No:
		return SceneCommand(GameSceneRequest::Push, GameSceneType::Playing);
	default:
		break;
	}
	return SceneCommand(GameSceneRequest::None);
}
