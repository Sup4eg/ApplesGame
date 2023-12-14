#include "Player.h"
#include "Game.h"

namespace ApplesGame {

  void initPlayer(Player& player, const Game & game) {
	//Init player state
	player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGTH / 2.f };
	player.speed = INITIAL_SPEED;
	player.direction = PlayerDirection::Right;

	// init plyaer sprite
	player.sprite.setTexture(game.playerTexture);
	setSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
	setSpriteRelativeOrigin(player.sprite, 0.5f, 0.5f);
  }

  void drawPlayer(Player& player, sf::RenderWindow& window) {
	player.sprite.setPosition(player.position.x, player.position.y);
	window.draw(player.sprite);
  }

}
