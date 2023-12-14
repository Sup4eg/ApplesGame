#include "Apple.h"
#include "Constants.h"

namespace ApplesGame {

  void initApple(Apple& apple) {
	//Init apples
	apple.position = getRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGTH);
	apple.shape.setRadius(APPLES_SIZE / 2.f);
	apple.shape.setFillColor(sf::Color::Green);
	apple.shape.setPointCount(100);
	apple.shape.setOrigin(APPLES_SIZE / 2.f, APPLES_SIZE / 2.f);
	apple.shape.setPosition(apple.position.x, apple.position.y);
  }
}
