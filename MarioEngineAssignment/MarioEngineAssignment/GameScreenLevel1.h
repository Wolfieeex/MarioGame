#pragma once
#ifndef GAMESCREENLEVEL1_H
#define GAMESCREENLEVEL1_H

#include "Constants.h"
#include "GameScreen.h"
#include "MarioCharacter.h"
#include "LuigiCharacter.h"

class Texture2D;
class MarioCharacter;
class LuigiCharacter;

class GameScreenLevel1 : GameScreen
{

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

private:
	Texture2D* m_background_texture;
	MarioCharacter* my_mario_character;
	LuigiCharacter* my_luigi_character;

	bool SetUpLevel();
};



#endif