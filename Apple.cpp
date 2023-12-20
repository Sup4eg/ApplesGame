#include "Apple.h"
#include "Constants.h"
#include "Game.h"

namespace ApplesGame {

  void initApple(Apple& apple, const Game & game) {
	//Init apples
	apple.isHidden = false;
	apple.position = getRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGTH);

	apple.sprite.setTexture(game.appleTexture);
	setSpriteSize(apple.sprite, APPLES_SIZE, APPLES_SIZE);
	setSpriteRelativeOrigin(apple.sprite);
  }

  void drawApple(Apple& apple, sf::RenderWindow& window)
  {
	apple.sprite.setPosition(apple.position.x, apple.position.y);
	window.draw(apple.sprite);
  }
}
