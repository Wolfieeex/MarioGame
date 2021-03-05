#pragma once
#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include "Constants.h"
#include <iostream>
#include <string>
#include <SDL.h>
#include "Texture2D.h"
#include <SDL_mixer.h>

class SoundEffect
{
private:
	Mix_Chunk* m_sound = nullptr;
	std::string m_path;

public:
	SoundEffect(std::string path);
	~SoundEffect();

	void Play();
};

#endif