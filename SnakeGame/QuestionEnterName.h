#pragma once
#include "SceneQuestionYesNo.h"


namespace SnakeGame {
    namespace Scene {
        class QuestionEnterName :
            public SceneQuestionYesNo
        {
        public:
            QuestionEnterName();

            // Унаследовано через SceneQuestionYesNo
            SceneCommand handlersQuestionYesNo(QuestionYesNo& cmd) override;

        };
    }
}

