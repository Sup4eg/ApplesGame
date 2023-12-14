#include <SFML/Graphics.hpp>
#include "Rock.h"
#include "Constants.h"

namespace ApplesGame {

  void initRock(Rock& rock) {
	//Init rocks
	rock.position = getRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGTH);
	rock.shape.setSize(sf::Vector2f(ROCKS_SIZE, ROCKS_SIZE));
	rock.shape.setFillColor(sf::Color::Magenta);
	rock.shape.setOrigin(ROCKS_SIZE / 2.f, ROCKS_SIZE / 2.f);
	rock.shape.setPosition(rock.position.x, rock.position.y);
  }

}