#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace ApplesGame {
  
  using namespace sf;

  //game over text
  struct GameOverText {
	sf::Text text;

	const Text::Style style = Text::Bold;
	const Color color = Color::White;
	const int size = 100;
	const std::string str = "GAME OVER";
  };

  struct GameOverBackground {
	sf::RectangleShape background;
	sf::Color color = sf::Color::Red;
  };

  struct GameOverState {

	GameOverText text;
	GameOverBackground background;
  };

  void initGameOver(GameOverState& gameOverState, const Font & font);
  void drawGameOverState(const GameOverState& gameOverState, sf::RenderWindow& window);

  //usage only this file
  static void initGameOverText(GameOverText & gameOverText, const Font& font);
  static void initGameOverBackground(GameOverBackground & gameOverSBackground);
}