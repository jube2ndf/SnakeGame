#pragma once

namespace SnakeGame {
	class GameSettings
	{
		static unsigned __int8 lvl;

		static bool GAME_MUSIC;
		static bool GAME_VOLUME;
	public:

		static void setLVL(int s);

		static int getLVL();

		static void setGameMusic(bool f);

		static bool getGameMusic();

		static void setGameVolume(bool f);

		static bool getGameVolume();
	};
}
