#pragma once
#ifndef LUIGICHARACTER_H
#define LUIGICHARACTER_H

#include "Character.h"

class LevelMap;
class LuigiCharacter : public Character
{
public:
	LuigiCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map);
	~LuigiCharacter();

	void Update(float deltaTime, SDL_Event e) override;
};

#endif
