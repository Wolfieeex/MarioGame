#include "MarioCharacter.h"
#include "Texture2D.h"
#include <string>
#include "LevelMap.h"

MarioCharacter::MarioCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{
	m_points = 0;
}

MarioCharacter::~MarioCharacter()
{

}

void MarioCharacter::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = true;
			break;
		case SDLK_RIGHT:
			m_moving_right = true;
			break;
		case SDLK_UP:
			if (m_can_jump)
			{
				m_jump_force = INITIAL_JUMP_FORCE;
				m_jumping = true;
			}
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			m_moving_left = false;
			break;
		case SDLK_RIGHT:
			m_moving_right = false;
			break;
		}
		break;
	}

	Character::Update(deltaTime, e);

}

void MarioCharacter::AddPoints()
{
	m_points++;
}
