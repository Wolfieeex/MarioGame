#pragma once
#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SDL.h>

class GameScreen
{
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	//unsigned int* m_score;

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	//virtual unsigned int* ReturnScore() { return m_score; }
protected:
	SDL_Renderer* m_renderer;
};

#endif 
