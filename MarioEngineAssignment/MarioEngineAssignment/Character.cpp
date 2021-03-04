
#include "Character.h"
#include "LevelMap.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map)
{
	m_alive = true;
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

	m_current_level_map = map;
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

	//collision position variables
	int centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;

	//deal with gravity
	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		//collided with ground so we can jump again
		m_can_jump = true;
	}


	if (m_moving_left && m_position.x > 0)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right && m_position.x < SCREEN_WIDTH - 34)
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

void Character::SetAlive(bool isAlive)
{
	m_alive = isAlive;
}

void Character::EnemyJump(float deltatime, float jumpForce)
{
	m_jump_force = jumpForce;
	m_jumping = true;
	Jump(deltatime);
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
