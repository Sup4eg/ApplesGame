#include <cassert>
#include <iostream>

#include "Game.h"


namespace ApplesGame {

  void chooseGameRegime(Menu& menu, Game& game)
  {
	//need to set apple regime
	if (!(game.regime & 1 << 2)) {
	  game.menu.text.text.setString(game.menu.text.appleRegimeStr);
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		game.regime |= (1 << 1) | (1 << 2); //set 1 bit to 1 (final apples) and 2 bit to 1 (move to acceleration choice text)
	  }
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		game.regime |= 1 << 2; //1 bit is 0 always, no need to change it (infinite apples), set 2 bit to 1,  (move to acceleration choice text)
	  }
	}
	else {
	  //need to set acceleration regime
	  game.menu.text.text.setString(game.menu.text.accelerationRegimeStr);
	  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
		game.regime = (game.regime | 1); // set 0 bit to 1 (with acceleration)
		game.gameState ^= 1 << 1; //invert game state bit 1 from 1 to 0(close menu)
	  }
	  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
		// 0 bit is 0 always, no need to change it (no acceleration)
		game.gameState ^= 1 << 1; // invert game state bit 1 from 1 to 0 (close menu)
	  }
	}
  }

  void restartGame(Game& game) {
	initPlayer(game.player, game);

	for (int i = 0; i < NUM_APPLES; ++i) {
	  initApple(game.apples[i], game);
	}

	for (int i = 0; i < NUM_ROCKS; ++i) {
	  initRock(game.rocks[i], game);
	}

	game.numEatenApples = 0;
	updateScore(game.score, game);
	game.gameState = 1 << 1;
	game.regime = '\0';
  }

  void initGame(Game& game) {

	//Init textures
	assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "/Player.png"));
	assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "/Apple.png"));
	assert(game.rockTexture.loadFromFile(RESOURCES_PATH + "/Rock.png"));

	//Init font
	assert(game.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

	initMenu(game.menu, game.font);
	initGameOver(game.gameOverState, game.font);
	initGameWinnedState(game.gameWinnedState, game.font);
	initControlHint(game.controlHint, game.font);
	initGameSoundBuffer(game.soundBuffer);
	initScore(game.score, game.font);
	restartGame(game);
  }

  void updateGame(Game& game, const float& deltaTime) {

	//no need menu
	// if game continues and no need to show menu
	if (!((game.gameState & 1 << 2) || (game.gameState & 1 << 1))) {

	  definePlayerDirection(game.player);
	  rotatePlayer(game.player);

	  defineNewPlayerCoordinates(game.player, deltaTime);

	  //Find player collision with apples
	  for (int i = 0; i < NUM_APPLES; ++i) {
		if (isCirclesCollide(game.player.position, PLAYER_SIZE / 2.f, game.apples[i].position, APPLES_SIZE / 2.f)) {
		  ++game.numEatenApples;

		  //update score here
		  updateScore(game.score, game);

		  if (game.regime & 1) {
			//Speed up player here
			game.player.speed += ACCELERATION;
		  }


		  //play apple eaten sound
		  game.player.sound.appleEatSound.play();

		  //Choose apple action after collision depends on game regime

		  if (!(game.regime & 1 << 1)) {
			//final number of apples
			game.apples[i].position = getRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGTH);
		  }
		  else {
			game.apples[i].position = { 0.f, 0.f };
			game.apples[i].isHidden = true;

			//Win state
			if (game.numEatenApples == NUM_APPLES) {
			  game.gameState |= 1 | (1 << 2); //finish game, WIN state
			  game.timeSinceGameFinish = 0;
			  game.player.sound.applauseSound.play();
			}
		  }
		}
	  }

	  //Find player collision with rocks
	  bool isCollideWithRocks = false;
	  for (int i = 0; i < NUM_ROCKS; ++i) {
		if (isRectanglesCollide(game.player.position, { PLAYER_SIZE, PLAYER_SIZE }, game.rocks[i].position, { ROCKS_SIZE, ROCKS_SIZE })) {
		  isCollideWithRocks = true;
		  break;
		}
	  }

	  //GAME OVER statements
	  if (isCollideWithRocks || isPlayerCollideWithScreen(game.player.position, PLAYER_SIZE, SCREEN_WIDTH, SCREEN_HEIGTH)) {
		game.gameState |= 1 << 2; //finish game, 0 bit is 0 by default, no need to set
		game.timeSinceGameFinish = 0;

		//play game over sound
		game.player.sound.deathSound.play();
	  }
	} else if (game.gameState & 1 << 1) {
	  chooseGameRegime(game.menu, game);
	}
	else {
	  if (game.timeSinceGameFinish <= PAUSE_LENGTH) {
		game.timeSinceGameFinish += deltaTime;
	  }
	  else {
		restartGame(game);
	  }
	}
  }


  void drawGame(Game& game, sf::RenderWindow& window) {


	drawPlayer(game.player, window);

	//Render apples
	for (int i = 0; i < NUM_APPLES; ++i) {
	  if (!game.apples[i].isHidden) {
		drawApple(game.apples[i], window);
	  }
	}

	//Render rocks
	for (int i = 0; i < NUM_ROCKS; ++i) {
	  drawRock(game.rocks[i], window);
	}

	drawControlHint(game.controlHint, window);

	//if game finished
	if (game.gameState & 1 << 2) {
	  if (game.gameState & 1) {
		drawGameWinnedState(game.gameWinnedState, window);
	  }
	  else {
		drawGameOverState(game.gameOverState, window);
	  }
	}

	drawScore(game.score, window);


	//need menu
	if (game.gameState & 1 << 1) {
	  drawMenu(game.menu, window);
	}

  }

  void deinitializeGame(const Game& game) {}
}
