#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Constants.h"
#include <iostream>
#include <string>
#include <SDL.h>

class Texture2D;

class Character
{
private:
	FACING m_facing_direction;
	
protected:
	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;

	bool m_moving_left;
	bool m_moving_right;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;

public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

	virtual void AddGravity(float deltaTime);
	virtual void Jump(float deltaTime);
};

#endif