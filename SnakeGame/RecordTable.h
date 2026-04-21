#pragma once
#include <vector>
#include <string>
#include "Record.h"
namespace SnakeGame {
	namespace Models {
		class RecordTable
		{
		private:
			static std::vector<Record> _top;
			static void Load(std::string file);
			static void Save(std::string file);
		public:
			static const std::vector<Record> GetTop();
			static const int getScore(std::string name);
			static void Add(Record adddValue);
			static void Load();
		};
	}
}


