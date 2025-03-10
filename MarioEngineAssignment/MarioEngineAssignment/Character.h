#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Constants.h"
#include <iostream>
#include <string>
#include <SDL.h>
#include "Texture2D.h"


class Texture2D;
class LevelMap;

class Character
{
protected:
	bool m_alive;

	float m_collision_radius;

	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;

	bool m_moving_left;
	bool m_moving_right;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	LevelMap* m_current_level_map;
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	FACING m_facing_direction;

public:

	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map);
	~Character();

	bool IsJumping() { return m_jumping; }
	void CancelJump() { m_jumping = false; }
	bool IsInAir() { return  !m_can_jump; }
	float GetJumingForce() { return m_jump_force; }

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

	virtual void AddGravity(float deltaTime);
	virtual void Jump(float deltaTime);

	void SetAlive(bool isAlive);
	void EnemyJump(float deltatime, float jumpForce);
	bool GetAlive() { return m_alive; }

	float GetCollisionRadius();

	Rect2D GetCollisionBox()
	{
		return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight());
	}

	virtual Circl2D GetCollisionCircle()
	{
		return Circl2D(m_position.x, m_position.y, m_collision_radius);
	}

};

#endif
