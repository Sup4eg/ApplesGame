#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Constants.h"
#include "Math.h"

namespace ApplesGame {
  
  using namespace sf;


  enum class ArrowType {
	LEFT, 
	RIGHT, 
	UP, 
	DOWN
  };

  struct Arrow {
	Text text;
	Sprite sprite;
	float spriteAngle;
	std::string str;
	Position2D position;
  };

  struct ControlHint {

	//arrows
	Arrow left;
	Arrow right;
	Arrow up;
	Arrow down;

	//General settings
	const Text::Style style = Text::Bold;
	const Color color = Color::Yellow;
	const int size = 20;

	//Gap between arrow and text
	const float arrowTextGap = 40.f;
	//Resources
	sf::Texture texture;
  };

  struct Game;

  void initControlHint(ControlHint& controlHint, const Font& font);

  void drawControlHint(const ControlHint& controlHint, sf::RenderWindow& window);

  //usage only this file
  static void initHint(const ControlHint& controlHint, Arrow& Arrow, const ArrowType& arrowType, const Font& font);
  static void setArrow(Arrow& arrow, const ArrowType& type);

}