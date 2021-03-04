#include "CharacterGoomba.h"

CharacterGoomba::CharacterGoomba(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D start_position, float movement_speed) : Character(renderer, imagePath, start_position, map)
{
	m_walking_iterration = 0;
	m_animation_transition = WALKING_ANIMATION_COOLDOWN;
	m_movement_speed = movement_speed;
	m_single_sprite_w = m_texture->GetWidth();
	m_single_sprite_h = m_texture->GetHeight() / 2;
	m_facing_direction = FACING_LEFT;
}

void CharacterGoomba::Render()
{

	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y) + m_single_sprite_h, m_single_sprite_w, m_single_sprite_h };

	SDL_Rect portion_of_sprite = { 0, m_walking_iterration * m_single_sprite_h, m_single_sprite_w, m_single_sprite_h };

	m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);

}

void CharacterGoomba::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	if (m_position.x < 1)
	{
		m_facing_direction = FACING_RIGHT;
	}

	if (m_position.x > SCREEN_WIDTH - 34)
	{
		m_facing_direction = FACING_LEFT;
	}

	m_animation_transition -= deltaTime;

	if (m_animation_transition <= 0)
	{
		if (m_walking_iterration == 0)
		{
			m_animation_transition = WALKING_ANIMATION_COOLDOWN;
			m_walking_iterration++;
		}
		else
		{
			m_animation_transition = WALKING_ANIMATION_COOLDOWN;
			m_walking_iterration = 0;
		}
	}

	if (m_facing_direction == FACING_LEFT)
	{
		m_moving_left = true;
		m_moving_right = false;
	}
	else if (m_facing_direction == FACING_RIGHT)
	{
		m_moving_right = true;
		m_moving_left = false;
	}
}

void CharacterGoomba::TakeDamage()
{
	m_alive = false;
}

void CharacterGoomba::MoveLeft(float deltaTime)
{
	m_facing_direction = FACING_LEFT;
	m_position.x -= deltaTime * GOOMBA_SPEED;
}

void CharacterGoomba::MoveRight(float deltaTime)
{
	m_facing_direction = FACING_RIGHT;
	m_position.x += deltaTime * GOOMBA_SPEED;
}

void CharacterGoomba::AddGravity(float deltaTime)
{
	if (m_position.y + 0 <= SCREEN_HEIGHT)
	{
		m_position.y += GRAVITY * deltaTime;
		m_can_jump = false;
	}
	else
	{
		m_can_jump = true;
	}
}
