#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "Math.h"
#include "Player.h"

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
	sf::RectangleShape background;

	//Resources
	sf::Texture playerTexture;

  };

  void definedirection(Game& game);

  void defineNewPlayerCoordinates(Game& game, const float& deltaTime);

  void restartGame(Game& game);

  void initGame(Game& game);

  void updateGame(Game& game, const float& deltaTime);

  void drawGame(Game& game, sf::RenderWindow& window);

  void deinitializeGame(const Game& game);
}
