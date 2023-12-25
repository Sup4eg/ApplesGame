#include "GameWinnedState.h"
#include "Constants.h"
#include "Math.h"

namespace ApplesGame {
  
  void initGameWinnedState(GameWinnedState& gameWinnedState, const Font& font)
  {
	initGameWinnedText(gameWinnedState.text, font);
	initGameWinnedBackground(gameWinnedState.background);
  }

  void drawGameWinnedState(const GameWinnedState& gameWinnedState, sf::RenderWindow& window)
  {
	window.draw(gameWinnedState.background.background);
	window.draw(gameWinnedState.text.text);

  }

  void initGameWinnedText(GameWinnedText& gameWinnedText, const Font& font)
  {
	gameWinnedText.text.setFont(font);
	gameWinnedText.text.setCharacterSize(gameWinnedText.size);
	gameWinnedText.text.setStyle(gameWinnedText.style);
	gameWinnedText.text.setFillColor(gameWinnedText.color);
	gameWinnedText.text.setString(gameWinnedText.str);
	setTextRelativeOrigin(gameWinnedText.text);
	gameWinnedText.text.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGTH / 2.f);
  }

  void initGameWinnedBackground(GameWinnedBackground& gameWinnedBackground)
  {
	gameWinnedBackground.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGTH));
	gameWinnedBackground.background.setFillColor(gameWinnedBackground.color);
	gameWinnedBackground.background.setPosition(0.f, 0.f);
  }
}


