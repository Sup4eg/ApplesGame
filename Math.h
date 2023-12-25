#pragma once

namespace sf {
  class Sprite;
  class Text;
}

namespace ApplesGame {

  struct Vector2D
  {
	float x = 0;
	float y = 0;
  };

  typedef Vector2D Position2D;

  Position2D getRandomPositionInScreen(const int& screenWidth, const int& screenHeight);

  int getRandomNumber(const int minN, const int maxN);

  bool isPlayerCollideWithScreen(Position2D position, float playerSize, float screenWidth, float screenHeight);

  bool isRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size);

  bool isCirclesCollide(Position2D circle1Position, float circle1Radius, Position2D circle2Position, float circle2Radius);

  void setSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);

  void setSpriteRelativeOrigin(sf::Sprite& sprite);

  void setTextRelativeOrigin(sf::Text& text);

  float getAngle(float angle);
}