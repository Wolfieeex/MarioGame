#pragma once
#ifndef MARIOCHARACTER_H
#define MARIOCHARACTER_H

#include "Character.h"

class LevelMap;
class MarioCharacter : public Character
{
public:
	MarioCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map);
	~MarioCharacter();

	void Update(float deltaTime, SDL_Event e) override;
	void AddPoints();

private:
	unsigned int m_points;
};

#endif