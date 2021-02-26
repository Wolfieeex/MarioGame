#pragma once
#ifndef GAMESCREENLEVEL1_H
#define GAMESCREENLEVEL1_H

#include "Constants.h"
#include "GameScreen.h"
#include "MarioCharacter.h"
#include "LuigiCharacter.h"

class PowBlock;
class Texture2D;
class MarioCharacter;
class LuigiCharacter;
class LevelMap;

class GameScreenLevel1 : GameScreen
{

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void UpdatePOWBlock();

private:
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	Texture2D* m_background_texture;
	MarioCharacter* my_mario_character;
	LuigiCharacter* my_luigi_character;

	bool SetUpLevel();
	void DoScreenShake();
	void SetLevelMap();

	LevelMap* m_level_map;

	PowBlock* m_pow_block;
};



#endif