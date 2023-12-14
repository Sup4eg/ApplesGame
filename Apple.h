#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame {

  struct Apple {
	Position2D position;
	sf::CircleShape shape;
  };

  void initApple(Apple& apple);
}

