#pragma once
#include <string>
namespace SnakeGame {
	namespace Models {
		struct Record
		{
			std::string Name;
			int score;
			bool operator<(const Record& other) const
			{
				return score > other.score;
			}
		};

	}
}