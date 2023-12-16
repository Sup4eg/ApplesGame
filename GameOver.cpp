#include "GameOver.h"
#include "Math.h"
#include "Constants.h"

namespace ApplesGame {

  void initGameOver(GameOver& gameOver, const sf::Font& font)
  {
	initGameOverText(gameOver.text, font);
	initGameOverBackground(gameOver.background);
  }

  void drawGameOver(const GameOver& gameOver, sf::RenderWindow& window)
  {
	window.draw(gameOver.background.background);
	window.draw(gameOver.text.text);
  }
  
  void initGameOverText(GameOverText& gameOverText, const Font& font)
  {
	gameOverText.text.setFont(font);
	gameOverText.text.setCharacterSize(gameOverText.size);
	gameOverText.text.setStyle(gameOverText.style);
	gameOverText.text.setFillColor(gameOverText.color);
	gameOverText.text.setString(gameOverText.str);
	setTextRelativeOrigin(gameOverText.text);
	gameOverText.text.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGTH / 2.f);
  }

  void initGameOverBackground(GameOverBackground& gameOverBackground)
  {
	gameOverBackground.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGTH));
	gameOverBackground.background.setFillColor(sf::Color::Red);
	gameOverBackground.background.setPosition(0.f, 0.f);

  }
}
