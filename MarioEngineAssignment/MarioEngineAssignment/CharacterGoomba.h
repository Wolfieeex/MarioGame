#pragma once
#ifndef CHARACTERGOOMBA_H
#define CHARACTERGOOMBA_H

#include "Character.h"

class CharacterGoomba : public Character
{
private:
	float m_movement_speed;
	float m_single_sprite_w;
	float m_single_sprite_h;
	unsigned int m_walking_iterration;
	float m_animation_transition;
public:
	CharacterGoomba(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D start_position, float movement_speed);
	~CharacterGoomba() {};

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void TakeDamage();
	void MoveLeft(float deltaTime) override;
	void MoveRight(float deltaTime) override;
	void AddGravity(float deltaTime) override;

	Circl2D GetCollisionCircle() override
	{
		return Circl2D(m_position.x, m_position.y + m_single_sprite_h, m_collision_radius);
	}
};

#endif 