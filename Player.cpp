#include "Player.h"
#include "Game.h"

namespace ApplesGame {

  void initPlayer(Player& player, const Game& game) {
	//Init player state
	player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGTH / 2.f };
	player.speed = INITIAL_SPEED;
	player.direction = PlayerDirection::Right;

	// init plyaer sprite
	player.sprite.setTexture(game.playerTexture);
	player.sprite.setRotation(getAngle(0.f));
	setSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
	setSpriteRelativeOrigin(player.sprite);

	//init player sound
	initPlayerSound(player.sound, game.soundBuffer);
  }

  void rotatePlayer(Player& player) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
	  player.sprite.setRotation(getAngle(0.f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
	  player.sprite.setRotation(getAngle(180.f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
	  player.sprite.setRotation(getAngle(90.f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
	  player.sprite.setRotation(getAngle(270.f));
	}
  }

  void reflectPlayer(Player& player) {

	auto playerScale = player.sprite.getScale();
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
	  player.sprite.setScale(fabs(playerScale.x), fabs(playerScale.y));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
	  player.sprite.setScale(fabs(playerScale.x), -fabs(playerScale.y));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
	  player.sprite.setScale(playerScale.x, fabs(playerScale.y));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
	  player.sprite.setScale(playerScale.x, -fabs(playerScale.y));
	}
  }

  void definePlayerDirection(Player& player) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
	  player.direction = PlayerDirection::Right;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
	  player.direction = PlayerDirection::Left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
	  player.direction = PlayerDirection::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
	  player.direction = PlayerDirection::Down;
	}
  }

  void defineNewPlayerCoordinates(Player& player, const float& deltaTime) {
	switch (player.direction)
	{
	case PlayerDirection::Right:
	{
	  player.position.x += player.speed * deltaTime;
	  break;
	}
	case PlayerDirection::Up:
	{
	  player.position.y -= player.speed * deltaTime;
	  break;
	}
	case PlayerDirection::Left:
	{
	  player.position.x -= player.speed * deltaTime;
	  break;
	}
	case PlayerDirection::Down:
	{
	  player.position.y += player.speed * deltaTime;
	  break;
	}
	}
  }

  void drawPlayer(Player& player, sf::RenderWindow& window) {
	player.sprite.setPosition(player.position.x, player.position.y);
	window.draw(player.sprite);
  }

}
