#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "ControlHint.h"
#include "Math.h"
#include "Player.h"
#include "GameSoundBuffer.h"
#include "GameOverState.h"
#include "GameWinnedState.h"
#include "Score.h"
#include "Menu.h"

namespace ApplesGame {
  
  struct Game {

	Player player;

	//Apples data
	Apple apples[NUM_APPLES];

	//Rocks data
	Rock rocks[NUM_ROCKS];

	//Global game data
	int numEatenApples = 0;
	float timeSinceGameFinish = 0.f;

	//mask
	// 0 bit - gameOver or gameWinned state
	// 1 bit - open menu or closed menu
	// 2 bit - isGameFinished true / false
	//0 0 0
	char gameState = 1 << 1; //open menu by default

	//Texts
	sf::Font font;
	GameOverState gameOverState;
	GameWinnedState gameWinnedState;
	Score score;
	ControlHint controlHint;
	Menu menu;

	//Resources
	sf::Texture playerTexture;
	sf::Texture appleTexture;
	sf::Texture rockTexture;

	//Sound buf
	GameSoundBuffer soundBuffer;

	//regimes, no regimes by default
	//mask
	//0 0 0
	//0 bit - acceleration true / false
	//1 bit - final or infinite apples true /false
	//2 bit - (user choice text for the menu, show apple regime text - 0 or acceleration regime text 1);
	char regime = '\0';
  };

  void chooseGameRegime(Menu& menu, Game& game);

  void restartGame(Game& game);

  void initGame(Game& game);

  void updateGame(Game& game, const float& deltaTime);

  void drawGame(Game& game, sf::RenderWindow& window);

  void deinitializeGame(const Game& game);
}
