#include "Math.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>

namespace ApplesGame {

  Position2D getRandomPositionInScreen(float screenWidth, float screenHeight) {
	Position2D result;
	result.x = rand() / (float)(RAND_MAX)*screenWidth;
	result.y = rand() / (float)(RAND_MAX)*screenHeight;
	return result;
  }

  bool isPlayerCollideWithScreen(Position2D position, float playerSize, float screenWidth, float screenHeight) {
	return (position.x - playerSize / 2.f < 0.f || position.x + playerSize / 2.f > screenWidth
	  || position.y - playerSize / 2.f < 0.f || position.y + playerSize / 2.f > screenHeight);
  }

  bool isRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size) {
	const float dx = (float)fabs(rect1Position.x - rect2Position.x);
	const float dy = (float)fabs(rect1Position.y - rect2Position.y);
	return (dx <= (rect1Size.x + rect2Size.x) / 2.f && dy <= (rect1Size.y + rect2Size.y) / 2.f);
  }

  bool isCirclesCollide(Position2D circle1Position, float circle1Radius, Position2D circle2Position, float circle2Radius) {
	const float dx = circle1Position.x - circle2Position.x;
	const float dy = circle1Position.y - circle2Position.y;
	return (pow(dx, 2) + pow(dy, 2) <= pow((circle1Radius + circle2Radius), 2));
  }

  void setSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
  {
	sf::FloatRect spriteRect = sprite.getLocalBounds();
	sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
	sprite.setScale(scale);
  }

  void setSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
  {
	sf::FloatRect spriteRect = sprite.getLocalBounds();
	sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
  }

}