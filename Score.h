#pragma once
#include <SFML/Graphics.hpp>


namespace ApplesGame {
  
  using namespace sf;

  struct Score {
	Text text;

	const Text::Style style = Text::Bold;
	const Color color = Color::White;
	const int size = 25;
	std::string str = "Score: 0";
  };

  struct Game;

  void initScore(Score & score, const Font & font);
  void updateScore(Score& score, const Game& game);
  void drawScore(const Score & score, sf::RenderWindow& window);

}
