#pragma once
#ifndef GAMESCREENLEVEL2_H
#define GAMESCREENLEVEL2_H

#include "Constants.h"
#include "GameScreen.h"
#include "MarioCharacter.h"
#include "LuigiCharacter.h"
#include <vector>


class PowBlock;
class Texture2D;
class MarioCharacter;
class LuigiCharacter;
class LevelMap;
class CharacterKoopa;
class CharacterCoin;
class CharacterGoomba;
class SoundEffect;

class GameScreenLevel2 : GameScreen
{
public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void UpdatePOWBlock();

protected:
	virtual void SetLevelMap();
	virtual bool SetUpLevel();

private:
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoin(Vector2D position);
	void CreateGoomba(Vector2D position, float speed);

	std::vector<CharacterKoopa*> m_enemies;
	std::vector<CharacterCoin*> m_coins;
	std::vector<CharacterGoomba*> m_enemies_goomba;

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	float m_enemy_spawn_cooldown;

	Texture2D* m_background_texture;
	MarioCharacter* my_mario_character;
	LuigiCharacter* my_luigi_character;

	SoundEffect* m_sound_beep;
	SoundEffect* m_sound_click;

	void DoScreenShake();

	LevelMap* m_level_map;

	PowBlock* m_pow_block;
};

#endif