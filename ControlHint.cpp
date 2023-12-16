#include <string>
#include <cassert>
#include <string>

#include "ControlHint.h"
#include "Game.h"

namespace ApplesGame {

  void initControlHint(ControlHint& controlHint, const Font& font) {

	//Init texture
	assert(controlHint.texture.loadFromFile(RESOURCES_PATH + "/Arrow.png"));

	initHint(controlHint, controlHint.left, ArrowType::LEFT, font);
	initHint(controlHint, controlHint.right, ArrowType::RIGHT, font);
	initHint(controlHint, controlHint.up, ArrowType::UP, font);
	initHint(controlHint, controlHint.down, ArrowType::DOWN, font);

  }

  //usage only this file
  void initHint(const ControlHint& controlHint, Arrow& arrow, const ArrowType& type, const Font& font) {
	
	setArrow(arrow, type);

	arrow.text.setFont(font);
	arrow.text.setCharacterSize(controlHint.size);
	arrow.text.setStyle(controlHint.style);
	arrow.text.setFillColor(controlHint.color);
	arrow.text.setString(arrow.str);
	arrow.text.setPosition(arrow.position.x, arrow.position.y);
	setTextRelativeOrigin(arrow.text);

	arrow.sprite.setTexture(controlHint.texture);
	arrow.sprite.setRotation(arrow.spriteAngle);
	setSpriteSize(arrow.sprite, ARROW_WIDTH, ARROW_HEIGHT);
	setSpriteRelativeOrigin(arrow.sprite);
	arrow.sprite.setPosition(arrow.position.x - controlHint.arrowTextGap, arrow.position.y);
  }


  void setArrow(Arrow & arrow, const ArrowType & type) {
	//by default left
	std::string str = "left";
	float spriteAngle = 180.f;
	float x = SCREEN_WIDTH - SCREEN_X_MARGIN;
	float y = SCREEN_Y_MARGIN;

	switch (type)
	{
	case ArrowType::RIGHT:
	  str = "right";
	  spriteAngle = 0.f;
	  y += 30.f;
	  break;
	case ArrowType::UP:
	  str = "up";
	  spriteAngle = 90.f;
	  x -= 100.f;
	  break;
	case ArrowType::DOWN:
	  str = "down";
	  spriteAngle = 270.f;
	  y += 30.f;
	  x -= 100.f;
	  break;
	}
	arrow.str = str;
	arrow.spriteAngle = spriteAngle;
	arrow.position = { x , y };
  }


  void drawControlHint(const ControlHint & controlHint, sf::RenderWindow& window) {
	window.draw(controlHint.left.sprite);
	window.draw(controlHint.left.text);

	window.draw(controlHint.right.sprite);
	window.draw(controlHint.right.text);

	window.draw(controlHint.up.sprite);
	window.draw(controlHint.up.text);

	window.draw(controlHint.down.sprite);
	window.draw(controlHint.down.text);
  }
}