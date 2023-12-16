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
  };

  struct GameOver {

	GameOverText text;
	GameOverBackground background;
  };

  void initGameOver(GameOver& gameOver, const Font & font);
  void drawGameOver(const GameOver& gameOver, sf::RenderWindow& window);

  //usage only this file
  static void initGameOverText(GameOverText & gameOverText, const Font& font);
  static void initGameOverBackground(GameOverBackground & gameOverBackground);
}