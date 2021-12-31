#pragma once

#include <string>
#include <map>
#include <iostream>
#include "SDL_mixer.h"

class SoundEffectManager {
public:
	void addSoundEffect(std::string name, std::string path);
	void playSoundEffect(std::string name);
	void stopSoundEffects();
private:
	std::map<std::string, Mix_Chunk*> effectsMap;
};
