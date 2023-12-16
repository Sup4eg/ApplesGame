#include <cassert>
#include "GameSoundBuffer.h"
#include "Constants.h"

namespace ApplesGame {
  
  void initGameSoundBuffer(GameSoundBuffer & soundBuf) {
	//Init sound buffers
	assert(soundBuf.deathBuf.loadFromFile(RESOURCES_PATH + "/Death.wav"));
	assert(soundBuf.appleEatBuf.loadFromFile(RESOURCES_PATH + "/AppleEat.wav"));
  }

}