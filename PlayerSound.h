#pragma once
#include <SFML/Audio/Sound.hpp>

namespace ApplesGame {
  
  struct PlayerSound {
	sf::Sound appleEatSound;
	sf::Sound deathSound;
	sf::Sound applauseSound;
  };

  struct GameSoundBuffer;

  void initPlayerSound(PlayerSound & sound, const GameSoundBuffer& soundBuf);

}
