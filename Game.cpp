#include "Game.h"
#include <cassert>

namespace ApplesGame {

  void restartGame(Game& game) {
	initPlayer(game.player, game);

	for (int i = 0; i < NUM_APPLES; ++i) {
	  initApple(game.apples[i], game);
	}

	for (int i = 0; i < NUM_ROCKS; ++i) {
	  initRock(game.rocks[i], game);
	}

	game.numEatenApples = 0;
	game.isGameFinished = false;
  }

  void initGame(Game& game) {

	//Init textures
	assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "/Player.png"));
	assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "/Apple.png"));
	assert(game.rockTexture.loadFromFile(RESOURCES_PATH + "/Rock.png"));

	//Init font
	assert(game.font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

	initGameOver(game.gameOver, game.font);
	initControlHint(game.controlHint, game.font);
	initGameSoundBuffer(game.soundBuffer);
	initScore(game.score, game.font);
	restartGame(game);
  }

  void updateGame(Game& game, const float& deltaTime) {
	if (!game.isGameFinished) {

	  definePlayerDirection(game.player);
	  rotatePlayer(game.player);
	  reflectPlayer(game.player);

	  defineNewPlayerCoordinates(game.player, deltaTime);

	  //Find player collision with apples
	  for (int i = 0; i < NUM_APPLES; ++i) {
		if (isCirclesCollide(game.player.position, PLAYER_SIZE / 2.f, game.apples[i].position, APPLES_SIZE / 2.f)) {
		  ++game.numEatenApples;

		  //update score here
		  updateScore(game.score, game);

		  //Speed up player here
		  game.player.speed += ACCELERATION;

		  //play apple eaten sound
		  game.player.sound.appleEatSound.play();

		  //Hide apples and rerender in with new coordinates
		  game.apples[i].position = getRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGTH);
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
		game.isGameFinished = true;
		game.timeSinceGameFinish = 0;
		
		//play game over sound
		game.player.sound.deathSound.play();		
	  }
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
	  drawApple(game.apples[i], window);
	}

	//Render rocks
	for (int i = 0; i < NUM_ROCKS; ++i) {
	  drawRock(game.rocks[i], window);
	}

	drawControlHint(game.controlHint, window);

	if (game.isGameFinished) {
	  drawGameOver(game.gameOver, window);
	}

	drawScore(game.score, window);

  }

  void deinitializeGame(const Game& game) {}
}
