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


//generate one rectangle shape
void initNewRectangleShape(sf::RectangleShape &shape, const float& playerX, const float& playerY, const float &size) {
  shape.setSize(sf::Vector2f(size, size));
  shape.setFillColor(sf::Color::Red);
  shape.setOrigin(size / 2.f, size / 2.f);
  shape.setPosition(playerX, playerY);
}

//generate shapes for array. This function can be used for different poligons: circle, trianble...
void initNewCircleShapesWithRandomPosition(sf::CircleShape* shapes, int arrLength,  float* shapesX, float* shapesY,  const float &size, const sf::Color color = sf::Color::Green, unsigned int points = 100) {

  for (int i = 0; i < arrLength; ++i) {
	shapesX[i] = rand() / (float)(RAND_MAX)*SCREEN_WIDTH;
	shapesY[i] = rand() / (float)(RAND_MAX)*SCREEN_HEIGTH;

	shapes[i].setRadius(size / 2.f);
	shapes[i].setFillColor(color);
	shapes[i].setPointCount(points);
	shapes[i].setOrigin(size / 2.f, size / 2.f);
	shapes[i].setPosition(shapesX[i], shapesY[i]);
  }

}

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

bool checkIsPlayerOut(float& playerX, float& playerY) {
  if (playerX - PLAYER_SIZE / 2.f < 0.f || playerX + PLAYER_SIZE / 2.f > SCREEN_WIDTH
	|| playerY - PLAYER_SIZE / 2.f < 0.f || playerY + PLAYER_SIZE / 2.f > SCREEN_HEIGTH) {
	return true;
  }
  return false;
}

void defineAppleCollisions(const float &playerX, const float &playerY, float * applesX, float * applesY, int &numEatenApples, sf::CircleShape* applesShape) {
  for (int i = 0; i < NUM_APPLES; ++i) {
	float dx = playerX - applesX[i];
	float dy = playerY - applesY[i];
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
  for (int i = 0; i < NUM_ROCKS; ++i) {
	float dx = playerX - rocksX[i];
	float dy = playerY - rocksY[i];
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
  initNewRectangleShape(playerShape, playerX, playerY, PLAYER_SIZE);

  //Init apples
  float applesX[NUM_APPLES];
  float applesY[NUM_APPLES];
  sf::CircleShape applesShape[NUM_APPLES];
  initNewCircleShapesWithRandomPosition(applesShape, NUM_APPLES, applesX, applesY, APPLES_SIZE);

  //Init rocks
  float rocksX[NUM_ROCKS];
  float rocksY[NUM_ROCKS];
  sf::CircleShape rocksShape[NUM_ROCKS];
  initNewCircleShapesWithRandomPosition(rocksShape, NUM_ROCKS, rocksX, rocksY, ROCKS_SIZE, sf::Color::Magenta, 3);

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

	//Rerender apples
	for (int i = 0; i < NUM_APPLES; ++i) {
	  window.draw(applesShape[i]);
	}
	//Rerender rocks
	for (int i = 0; i < NUM_ROCKS; ++i) {
	  window.draw(rocksShape[i]);
	}
	//Rerender player
	window.draw(playerShape);
	window.display();
  }

  return 0;
}
