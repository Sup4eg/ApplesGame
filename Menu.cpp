#include "Menu.h"
#include "Math.h"
#include "Constants.h"
#include "Game.h"

namespace ApplesGame {

  using namespace std;

  void initMenu(Menu& menu, const Font& font)
  {
	initMenuText(menu.text, font);
	initMenuBackground(menu.background);
  }

  void drawMenu(const Menu& menu, sf::RenderWindow& window)
  {
	window.draw(menu.background.background);
	window.draw(menu.text.text);
  }

  void initMenuText(MenuText& menuText, const Font& font) {
	menuText.text.setFont(font);
	menuText.text.setCharacterSize(menuText.size);
	menuText.text.setStyle(menuText.style);
	menuText.text.setFillColor(menuText.color);
	menuText.text.setString(menuText.appleRegimeStr);


	setTextRelativeOrigin(menuText.text);
	menuText.text.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGTH / 2.f);
  }

  void initMenuBackground(MenuBackground& menuBackground) {
	menuBackground.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGTH));
	menuBackground.background.setFillColor(menuBackground.color);
	menuBackground.background.setPosition(0.f, 0.f);
  }

}


