#pragma once
#ifndef LUIGICHARACTER_H
#define LUIGICHARACTER_H

#include "Character.h"

class LuigiCharacter : public Character
{
public:
	LuigiCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position);
	~LuigiCharacter();

	void Update(float deltaTime, SDL_Event e) override;
};

#endif
