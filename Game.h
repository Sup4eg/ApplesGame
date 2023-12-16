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
#include "GameOver.h"
#include "Score.h"

namespace ApplesGame {
  
  struct Game {

	Player player;

	//Apples data
	Apple apples[NUM_APPLES];

	//Rocks data
	Rock rocks[NUM_ROCKS];

	//Global game data
	int numEatenApples = 0;
	bool isGameFinished = false;
	float timeSinceGameFinish = 0.f;

	//Texts
	sf::Font font;
	GameOver gameOver;
	Score score;
	ControlHint controlHint;

	//Resources
	sf::Texture playerTexture;
	sf::Texture appleTexture;
	sf::Texture rockTexture;

	//Sound buf
	GameSoundBuffer soundBuffer;
  };

  void restartGame(Game& game);

  void initGame(Game& game);

  void updateGame(Game& game, const float& deltaTime);

  void drawGame(Game& game, sf::RenderWindow& window);

  void deinitializeGame(const Game& game);
}
