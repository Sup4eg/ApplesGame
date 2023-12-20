#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace ApplesGame {

  using namespace sf;

  //game over text
  struct MenuText {
	sf::Text text;

	const Text::Style style = Text::Bold;
	const Color color = Color::White;
	const int size = 30;

	//not change strings
	const std::string appleRegimeStr = "Choose regime of the game,\npress 1 or 2 on keyboard\n\n1. Final number of apples\n2. Infinite number of apples";

	const std::string accelerationRegimeStr = "Choose regime of the game,\npress 3 or 4 on keyboard\n\n3. With acceleration\n4. Without acceleration";

  };


  struct MenuBackground {
	sf::RectangleShape background;
	const sf::Color color = sf::Color::Blue;

  };

  struct Menu {

	MenuText text;
	MenuBackground background;
  };

  struct Game;

  void initMenu(Menu& menu, const Font& font);
  void drawMenu(const Menu& menu, sf::RenderWindow& window);

  static void initMenuText(MenuText& menuText, const Font& font);
  static void initMenuBackground(MenuBackground& menuBackground);
}