#pragma once
#include "Math.h"

namespace ApplesGame {

  struct Rock {
	Position2D position;
	sf::RectangleShape shape;
  };

  void initRock(Rock& rock);
}