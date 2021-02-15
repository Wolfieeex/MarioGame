#include "Character.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position)
{
	m_collision_radius = 15.0f;

	m_moving_left = false;
	m_moving_right = false;

	m_facing_direction = FACING_RIGHT;

	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture!" << std::endl;
	}
}

Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE);

	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}

}

void Character::Update(float deltaTime, SDL_Event e)
{
	//deal with jumping first
	if (m_jumping)
	{
		Jump(deltaTime);
	}

	AddGravity(deltaTime);

	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}

	
}

void Character::Jump(float deltaTime)
{
	//adjust position
	m_position.y -= m_jump_force * deltaTime;

	//reduce jump force
	m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

	//is jump force 0?
	if (m_jump_force <= 0.0f)
		m_jumping = false;
}

float Character::GetCollisionRadius()
{
	return m_collision_radius;
}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Character::GetPosition()
{
	return m_position;
}

void Character::MoveLeft(float deltaTime)
{
	m_facing_direction = FACING_LEFT;
	m_position.x -= deltaTime * MOVEMENTSPEED;
}

void Character::MoveRight(float deltaTime)
{
	m_facing_direction = FACING_RIGHT;
	m_position.x += deltaTime * MOVEMENTSPEED;
}

void Character::AddGravity(float deltaTime)
{
	if (m_position.y + 70 <= SCREEN_HEIGHT)
	{
		m_position.y += GRAVITY * deltaTime;
		m_can_jump = false;
	}
	else
	{
		m_can_jump = true;
	}
}