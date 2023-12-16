#pragma once
#include "Math.h"

namespace ApplesGame {

  struct Rock {
	Position2D position;
	sf::Sprite sprite;
  };

  struct Game;

  void initRock(Rock& rock, const Game& game);

  void drawRock(Rock& rock, sf::RenderWindow& window);
}