#pragma once
#ifndef SOUND_H
#define SOUND_H

#include "Constants.h"
#include <iostream>
#include <string>
#include <SDL.h>
#include "Texture2D.h"
#include <SDL_mixer.h>

class Sound
{
private:
	Mix_Chunk* m_sound = nullptr;
	std::string m_path;

public:
	Sound(std::string path);
	~Sound();

	void Play();
};

#endif