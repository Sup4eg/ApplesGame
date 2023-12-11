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
#include <string>
#include <math.h>

const std::string RESOURCES_PATH = "Resources/";
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGTH = 600;
const std::string GAME_NAME = "Apples game!";
const float INITIAL_SPEED = 100.f; // pixels per second
const float ACCELERATION = 50.f;

const float PLAYER_SIZE = 20.f;
const float APPLES_SIZE = 20.f;
const float ROCKS_SIZE = 30.f;

const int NUM_APPLES = 20;
const int NUM_ROCKS = 7;

//Understand player direction
void definePlayerDirection(int &playerDirection) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
	playerDirection = 0;
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
	playerDirection = 1;
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
	playerDirection = 2;
  }
  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
	playerDirection = 3;
  }
}

//Understand new player coordinates
void defineNewPlayerCoordinates(const int &playerDirection, const float &playerSpeed, const float &deltaTime, float &playerX, float &playerY) {
  if (playerDirection == 0) {
	playerX += playerSpeed * deltaTime;
  }
  else if (playerDirection == 1) {
	playerY -= playerSpeed * deltaTime;
  }
  else if (playerDirection == 2) {
	playerX -= playerSpeed * deltaTime;
  }
  else if (playerDirection == 3) {
	playerY += playerSpeed * deltaTime;
  }
}

//Restart game
void restartGame(sf::RectangleShape playerShape, float& playerX, float& playerY, float& playerSpeed, int& playerDirection, sf::RenderWindow &window) {
  //stop game
  window.close();

  playerX = SCREEN_WIDTH / 2.f;
  playerY = SCREEN_HEIGTH / 2.f;
  playerSpeed = INITIAL_SPEED;
  playerDirection = 0;
  playerShape.setPosition(playerX, playerY);

  //Rerender window here
  window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGTH), GAME_NAME);
}

bool checkIsPlayerOut(const float& playerX, const float& playerY) {
  if (playerX - PLAYER_SIZE / 2.f < 0.f || playerX + PLAYER_SIZE / 2.f > SCREEN_WIDTH
	|| playerY - PLAYER_SIZE / 2.f < 0.f || playerY + PLAYER_SIZE / 2.f > SCREEN_HEIGTH) {
	return true;
  }
  return false;
}

void defineAppleCollisions(const float &playerX, const float &playerY, float * applesX, float * applesY, int &numEatenApples, sf::CircleShape* applesShape) {
  for (int i = 0; i < NUM_APPLES; ++i) {
	const float dx = playerX - applesX[i];
	const float dy = playerY - applesY[i];
	if (pow(dx, 2) + pow(dy, 2) <= pow(((APPLES_SIZE + PLAYER_SIZE) / 2.f), 2)) {
	  ++numEatenApples;
	  //Hide apples and rerender in with new coordinates
	  applesX[i] = rand() / (float)(RAND_MAX)*SCREEN_WIDTH;
	  applesY[i] = rand() / (float)(RAND_MAX)*SCREEN_HEIGTH;
	  applesShape[i].setPosition(applesX[i], applesY[i]);
	}
  }
}

bool isRockCollision(const float& playerX, const float& playerY, float* rocksX, float* rocksY) {
  //Need iterator
  for (int i = 0; i < NUM_ROCKS; ++i) {
	const float dx = playerX - rocksX[i];
	const float dy = playerY - rocksY[i];
	if (pow(dx, 2) + pow(dy, 2) <= pow(((ROCKS_SIZE + PLAYER_SIZE) / 2.f), 2)) {
	  return true;
	}
  }
  return false;
}

int main()
{

  //Init window
  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGTH), GAME_NAME);

  //Init seed here
  int seed = (int)time(nullptr);
  srand(seed);

  //Init player state
  float playerX = SCREEN_WIDTH / 2.f;
  float playerY = SCREEN_HEIGTH / 2.f;
  float playerSpeed = INITIAL_SPEED;
  int playerDirection = 0; //0 - Right, 1 - Up, 2 - Left, 3 - Down


  //Init player shape
  sf::RectangleShape playerShape;
  playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
  playerShape.setFillColor(sf::Color::Red);
  playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
  playerShape.setPosition(playerX, playerY);

  //Init apples
  float applesX[NUM_APPLES];
  float applesY[NUM_APPLES];
  sf::CircleShape applesShape[NUM_APPLES];

  for (int i = 0; i < NUM_APPLES; ++i) {
	applesX[i] = rand() / (float)(RAND_MAX)*SCREEN_WIDTH;
	applesY[i] = rand() / (float)(RAND_MAX)*SCREEN_HEIGTH;

	applesShape[i].setRadius(APPLES_SIZE / 2.f);
	applesShape[i].setFillColor(sf::Color::Green);
	applesShape[i].setPointCount(100);
	applesShape[i].setOrigin(APPLES_SIZE / 2.f, APPLES_SIZE / 2.f);
	applesShape[i].setPosition(applesX[i], applesY[i]);
  }

  //Init rocks
  float rocksX[NUM_ROCKS];
  float rocksY[NUM_ROCKS];
  sf::CircleShape rocksShape[NUM_ROCKS];

  for (int i = 0; i < NUM_ROCKS; ++i) {
	rocksX[i] = rand() / (float)(RAND_MAX)*SCREEN_WIDTH;
	rocksY[i] = rand() / (float)(RAND_MAX)*SCREEN_HEIGTH;

	rocksShape[i].setRadius(ROCKS_SIZE / 2.f);
	rocksShape[i].setFillColor(sf::Color::Magenta);
	rocksShape[i].setPointCount(3);
	rocksShape[i].setOrigin(ROCKS_SIZE / 2.f, ROCKS_SIZE / 2.f);
	rocksShape[i].setPosition(rocksX[i], rocksY[i]);
  }


  int numEatenApples = 0;

  //Init game clock
  sf::Clock gameClock;
  float lastTime = gameClock.getElapsedTime().asSeconds();

  //Main loop
  while (window.isOpen())
  {
	//Calculate time delta
	float currentTime = gameClock.getElapsedTime().asSeconds();
	float deltaTime = currentTime - lastTime;
	lastTime = currentTime;

	sf::Event event;
	while (window.pollEvent(event))
	{
	  //close window here
	  if (event.type == sf::Event::Closed)
		window.close();
	}

	definePlayerDirection(playerDirection);
	
	//Speed up player here
	playerSpeed += ACCELERATION * deltaTime;
	
	defineNewPlayerCoordinates(playerDirection, playerSpeed, deltaTime, playerX, playerY);

	if (checkIsPlayerOut(playerX, playerY)) {
	  restartGame(playerShape, playerX, playerY, playerSpeed, playerDirection, window);
	}

	defineAppleCollisions(playerX, playerY, applesX, applesY, numEatenApples, applesShape);

	if (isRockCollision(playerX, playerY, rocksX, rocksY)) {
	  //finish game here if with one of the rock collision
	  window.close();
	  break;
	}

	//clear window after last draw. It always must be done for a new frame
	window.clear();
	playerShape.setPosition(playerX, playerY);

	//Render apples
	for (const auto &appleShape: applesShape) {
	  window.draw(appleShape);
	}
	//Render rocks
	for (const auto &rockShape: rocksShape) {
	  window.draw(rockShape);
	}
	//Rerender player
	window.draw(playerShape);
	window.display();
  }

  return 0;
}
