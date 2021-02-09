#pragma once
#ifndef GAMESCREENINTRO_H
#define GAMESCREENINTRO_H

#include "Constants.h"
#include "GameScreen.h"

class Texture2D;

class GameScreenIntro : GameScreen
{

public:
	GameScreenIntro(SDL_Renderer* renderer);
	~GameScreenIntro();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:
	Texture2D* m_background_texture;

	bool SetUpLevel();
};



#endif