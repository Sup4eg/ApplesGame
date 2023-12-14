#include "Game.h"
#include <cassert>

namespace ApplesGame {

  void definedirection(Game& game) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
	  game.player.direction = PlayerDirection::Right;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
	  game.player.direction = PlayerDirection::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
	  game.player.direction = PlayerDirection::Left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
	  game.player.direction = PlayerDirection::Down;
	}
  }

  void defineNewPlayerCoordinates(Game& game, const float& deltaTime) {
	switch (game.player.direction)
	{
	case PlayerDirection::Right:
	{
	  game.player.position.x += game.player.speed * deltaTime;
	  break;
	}
	case PlayerDirection::Up:
	{
	  game.player.position.y -= game.player.speed * deltaTime;
	  break;
	}
	case PlayerDirection::Left:
	{
	  game.player.position.x -= game.player.speed * deltaTime;
	  break;
	}
	case PlayerDirection::Down:
	{
	  game.player.position.y += game.player.speed * deltaTime;
	  break;
	}
	}
  }

  void restartGame(Game& game) {
	initPlayer(game.player, game);

	for (int i = 0; i < NUM_APPLES; ++i) {
	  initApple(game.apples[i]);
	}

	for (int i = 0; i < NUM_ROCKS; ++i) {
	  initRock(game.rocks[i]);
	}

	game.numEatenApples = 0;
	game.isGameFinished = false;
  }

  void initGame(Game& game) {

	assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "/Player.png"));

	game.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGTH));
	game.background.setFillColor(sf::Color::Black);
	game.background.setPosition(0.f, 0.f);

	restartGame(game);
  }

  void updateGame(Game& game, const float& deltaTime) {
	if (!game.isGameFinished) {

	  definedirection(game);
	  defineNewPlayerCoordinates(game, deltaTime);

	  //Find player collision with apples
	  for (int i = 0; i < NUM_APPLES; ++i) {
		if (isCirclesCollide(game.player.position, PLAYER_SIZE / 2.f, game.apples[i].position, APPLES_SIZE / 2.f)) {
		  ++game.numEatenApples;

		  //Speed up player here
		  game.player.speed += ACCELERATION;

		  //Hide apples and rerender in with new coordinates
		  game.apples[i].position = getRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGTH);
		}
	  }

	  //Find player collision with rocks
	  for (int i = 0; i < NUM_ROCKS; ++i) {
		if (isRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE }, game.rocks[i].position, { ROCKS_SIZE, ROCKS_SIZE })) {
		  game.isGameFinished = true;
		  game.timeSinceGameFinish = 0;
		}
	  }


	  if (isPlayerCollideWithScreen(game.player.position, PLAYER_SIZE, SCREEN_WIDTH, SCREEN_HEIGTH)) {
		game.isGameFinished = true;
		game.timeSinceGameFinish = 0;
	  }
	}
	else {
	  if (game.timeSinceGameFinish <= PAUSE_LENGTH) {
		game.timeSinceGameFinish += deltaTime;
		game.background.setFillColor(sf::Color::Red);
	  }
	  else {
		game.background.setFillColor(sf::Color::Black);
		restartGame(game);
	  }
	}

  }

  void drawGame(Game& game, sf::RenderWindow& window) {
	window.draw(game.background);
	drawPlayer(game.player, window);

	//Render apples
	for (int i = 0; i < NUM_APPLES; ++i) {
	  game.apples[i].shape.setPosition(game.apples[i].position.x, game.apples[i].position.y);
	  window.draw(game.apples[i].shape);
	}
	//Render rocks
	for (int i = 0; i < NUM_ROCKS; ++i) {
	  game.rocks[i].shape.setPosition(game.rocks[i].position.x, game.rocks[i].position.y);
	  window.draw(game.rocks[i].shape);
	}
  }

  void deinitializeGame(const Game& game) {}
}
