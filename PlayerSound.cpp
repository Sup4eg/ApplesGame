#include "PlayerSound.h"
#include "GameSoundBuffer.h"

namespace ApplesGame {
 
  void initPlayerSound(PlayerSound& sound, const GameSoundBuffer& soundBuf)
  {
	sound.deathSound.setBuffer(soundBuf.deathBuf);
	sound.appleEatSound.setBuffer(soundBuf.appleEatBuf);
  }

}
