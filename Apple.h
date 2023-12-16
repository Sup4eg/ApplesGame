#pragma once
#include <SFML/Graphics.hpp>
#include "Math.h"

namespace ApplesGame {

  struct Apple {
	Position2D position;
	sf::Sprite sprite;
  };

  struct Game;

  void initApple(Apple& apple, const Game & game);

  void drawApple(Apple& apple, sf::RenderWindow& window);
}