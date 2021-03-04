#pragma once
#ifndef CHARACTERKOOPA_H
#define CHARACTERKOOPA_H

#include "Character.h"

class CharacterKoopa : public Character
{
private:
	float m_movement_speed;
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;
	float m_cooldownTime;
	bool immune;

	void FlipRightwayUp();

public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~CharacterKoopa() {};

	void TakeDamage();
	void Jump();
	bool GetInjured() { return m_injured; }

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void MoveLeft(float deltaTime) override;
	void MoveRight(float deltaTime) override;
	void AddGravity(float deltaTime) override;
};

#endif
