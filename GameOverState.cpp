#include "GameOverState.h"
#include "Constants.h"
#include "Math.h"

namespace ApplesGame {

  void initGameOver(GameOverState& gameOverState, const sf::Font& font)
  {
	initGameOverText(gameOverState.text, font);
	initGameOverBackground(gameOverState.background);
  }

  void drawGameOverState(const GameOverState& gameOverState, sf::RenderWindow& window)
  {
	window.draw(gameOverState.background.background);
	window.draw(gameOverState.text.text);
  }
  
  void initGameOverText(GameOverText& gameOverStateText, const Font& font)
  {
	gameOverStateText.text.setFont(font);
	gameOverStateText.text.setCharacterSize(gameOverStateText.size);
	gameOverStateText.text.setStyle(gameOverStateText.style);
	gameOverStateText.text.setFillColor(gameOverStateText.color);
	gameOverStateText.text.setString(gameOverStateText.str);
	setTextRelativeOrigin(gameOverStateText.text);
	gameOverStateText.text.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGTH / 2.f);
  }

  void initGameOverBackground(GameOverBackground& gameOverStateBackground)
  {
	gameOverStateBackground.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGTH));
	gameOverStateBackground.background.setFillColor(gameOverStateBackground.color);
	gameOverStateBackground.background.setPosition(0.f, 0.f);
  }
}
