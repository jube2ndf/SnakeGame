#pragma once
#include <string>
namespace SnakeGame
{
	// Resources path
	const std::string RESOURCES_PATH = "Resources\\";

	const std::string FONTS_PATH    = RESOURCES_PATH + "Fonts\\";
	const std::string SOUNDS_PATH   = RESOURCES_PATH + "Sounds\\";
	const std::string TEXTURE_PATH  = RESOURCES_PATH + "Textures\\";
	const std::string FILE_RECORD_TOP = "top.txt";
	const int   MAX_RECORDS_TABLE_SIZE = 10;

	const float SNAKE_SIZE          = 20.f;
	const float APPLE_SIZE          = 20.f;
	const float ROCK_SIZE           = 20.f;
	const float INITIAL_SPEED       = 10.f;
	const float ACCELERATION        = 10.f; // For each eaten apple player speed will be increased by this value
	const int   ROCKS_COUNT         = 20;
	const int   INITIAL_SNAKE_SIZE  = 4;

	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEGHT = 600;
}