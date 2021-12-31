#include "SoundEffectManager.h"

void SoundEffectManager::addSoundEffect(std::string name, std::string path) {
	const char* pathChar = path.c_str();
	Mix_Chunk* chunk = Mix_LoadWAV(pathChar);
	if (chunk == NULL) {
		printf("Mix_LoadWAV: %s\n", Mix_GetError());
	}
	else {
		effectsMap[name] = chunk;
	}
}

void SoundEffectManager::playSoundEffect(std::string name) {
	Mix_PlayChannel(-1, effectsMap[name], 0);
}

void SoundEffectManager::stopSoundEffects() {
	Mix_ExpireChannel(-1, 1);
}
