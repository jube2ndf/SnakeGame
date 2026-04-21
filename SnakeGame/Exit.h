#pragma once
#include "SceneQuestionYesNo.h"

namespace SnakeGame {
	namespace Scene {
		class Exit:
			public SceneQuestionYesNo
		{

			
			// Унаследовано через SceneQuestionYesNo
			SceneCommand handlersQuestionYesNo(QuestionYesNo& cmd) override;

		public:
			Exit();
		};
	}
}

