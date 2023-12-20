#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Math.h"
#include "Constants.h"
#include "PlayerSound.h"

namespace ApplesGame {

  enum class PlayerDirection {
	Right = 0,
	Up,
	Left,
	Down
  };

  struct Player {
	Position2D position;
	float speed = INITIAL_SPEED;
	PlayerDirection direction = PlayerDirection::Right;
	sf::Sprite sprite;

	PlayerSound sound;
  };


  struct Game;

  void definePlayerDirection(Player& player);

  void rotatePlayer(Player& player);

  void defineNewPlayerCoordinates(Player& player, const float& deltaTime);

  void initPlayer(Player& player, const Game & game);

  void drawPlayer(Player & player, sf::RenderWindow & window);
}