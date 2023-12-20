#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace ApplesGame {

  using namespace sf;

  //game over text
  struct GameWinnedText {
	sf::Text text;

	const Text::Style style = Text::Bold;
	const Color color = Color::White;
	const int size = 100;
	const std::string str = "GAME WON!";
  };

  struct GameWinnedBackground {
	sf::RectangleShape background;
	sf::Color color = sf::Color::Green;
  };

  struct GameWinnedState {

	GameWinnedText text;
	GameWinnedBackground background;
  };

  void initGameWinnedState(GameWinnedState& gameWinnedState, const Font& font);
  void drawGameWinnedState(const GameWinnedState& gameWinnedState, sf::RenderWindow& window);

  //usage only this file
  static void initGameWinnedText(GameWinnedText& gameWinnedText, const Font& font);
  static void initGameWinnedBackground(GameWinnedBackground& gameWinnedBackground);
}
