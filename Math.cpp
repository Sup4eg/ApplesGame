#include "Math.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>

namespace ApplesGame {

  Position2D getRandomPositionInScreen(const int& screenWidth, const int& screenHeight) {
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

  void setSpriteRelativeOrigin(sf::Sprite& sprite)
  {
	sf::FloatRect spriteRect = sprite.getLocalBounds();
	sprite.setOrigin(spriteRect.left + spriteRect.width / 2.f, spriteRect.top + spriteRect.height / 2.f);
  }

  void setTextRelativeOrigin(sf::Text& text)
  {
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.f, textRect.top + textRect.height / 2.f);
  }

  float getAngle(float angle)
  {
	const float sfmlCoefficient = -1.f; //because SFML window has inverted axis
	return angle * sfmlCoefficient;
  }

}