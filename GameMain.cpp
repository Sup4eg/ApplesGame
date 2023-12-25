/**
 * @file ApplesGame.cpp
 *
 * @brief ApplesGame
 *
 * @author @sup4eg
 *
 */


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Game.h"


int main()
{
  using namespace ApplesGame;

  //Init window
  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGTH), GAME_NAME);

  //Init seed here
  int seed = (int)time(nullptr);
  srand(seed);

  //Game initialization
  Game game;
  initGame(game);

  //Init game clock
  sf::Clock gameClock;
  float lastTime = gameClock.getElapsedTime().asSeconds();

  //Main loop
  while (window.isOpen())
  {

	//Reduce framerate to not spam CPU and GPU
	sf::sleep(sf::milliseconds(16));

	//Calculate time delta
	float currentTime = gameClock.getElapsedTime().asSeconds();
	float deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	//Read events

	sf::Event event;
	while (window.pollEvent(event))
	{
	  //close window here
	  if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
		window.close();
		break;
	  }
	}
	//Update game state
	updateGame(game, deltaTime);

	// Draw game
	window.clear();
	drawGame(game, window);
	window.display();

  }

  //Deinitialization
  deinitializeGame(game);

  return 0;
}
