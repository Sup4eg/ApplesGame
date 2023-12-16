#include <SFML/Graphics.hpp>
#include "Rock.h"
#include "Constants.h"
#include "Game.h"

namespace ApplesGame {

  void initRock(Rock& rock, const Game& game) {
	//Init rocks
	rock.position = getRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGTH);

	rock.sprite.setTexture(game.rockTexture);
	setSpriteSize(rock.sprite, ROCKS_SIZE, ROCKS_SIZE);
	setSpriteRelativeOrigin(rock.sprite);
  }

  void drawRock(Rock& rock, sf::RenderWindow& window)
  {
	rock.sprite.setPosition(rock.position.x, rock.position.y);
	window.draw(rock.sprite);
  }

}