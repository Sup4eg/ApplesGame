#pragma once
#include <SFML/Audio.hpp>

namespace ApplesGame {

  struct GameSoundBuffer {
	sf::SoundBuffer deathBuf;
    sf::SoundBuffer appleEatBuf;
	sf::SoundBuffer applauseBuf;
  };

  void initGameSoundBuffer(GameSoundBuffer & soundBuf);
}