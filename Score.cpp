#include "Score.h"
#include "Game.h"

namespace ApplesGame {
  
  void initScore(Score& score, const Font & font) {

	score.text.setFont(font);
	score.text.setCharacterSize(score.size);
	score.text.setStyle(score.style);
	score.text.setFillColor(score.color);
	score.text.setString(score.str);
	setTextRelativeOrigin(score.text);
	score.text.setPosition(SCREEN_X_MARGIN, SCREEN_Y_MARGIN);
  }

  void updateScore(Score & score, const Game& game) {
	score.str = "Score: " + std::to_string(game.numEatenApples);
	score.text.setString(score.str);
  }

  void drawScore(const Score& score, sf::RenderWindow& window)
  {
	window.draw(score.text);
  }
}

