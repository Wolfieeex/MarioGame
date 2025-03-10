#include "CharacterKoopa.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, map)
{
	immune = false;
	m_cooldownTime = 1.0f;
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_injured = false;
	m_facing_direction = start_facing;

	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();
}

void CharacterKoopa::TakeDamage()
{
	if (!immune)
	{
		if (!m_injured)
		{
			m_injured = true;
			m_injured_time = INJURED_TIME;
			m_cooldownTime = INJURE_COOLDOWN;
			Jump();
		}
		else
		{
			m_alive = false;
		}
	}
}

void CharacterKoopa::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE_SMALL;
		m_jumping = true;
		m_can_jump = false;
	}

}

void CharacterKoopa::Render()
{
	//variable to hold the left position of the sprite we want to draw
	int left = 0.0f;

	//if injured move the left position to be the left position of the second image of the sprite sheet
	if (m_injured)
		left = m_single_sprite_w;


	//get the portion of the sprite sheet you want to draw
	//							   {xPos, yPos, width of sprite, height of sprite}
	SDL_Rect portion_of_sprite = { left,0,m_single_sprite_w, m_single_sprite_h };

	//determine where you want it drawn
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	//then draw it facing the correct direction
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}

}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	//use the code within the base class
	Character::Update(deltaTime, e);

	if (m_position.x < 1)
	{
		m_facing_direction = FACING_RIGHT;
	}

	if (m_position.x > SCREEN_WIDTH - 34)
	{
		m_facing_direction = FACING_LEFT;
	}

	if (!m_injured)
	{
		//enemy is not injured so move
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
	else
	{
		//we should not be moving when injured
		m_moving_right = false;
		m_moving_left = false;

		//count down the injured time
		m_injured_time -= deltaTime;
		m_cooldownTime -= deltaTime;

		if (m_injured_time <= 0.0)
			FlipRightwayUp();

		if (m_cooldownTime <= 0)
		{
			immune = false;
		}
		else
		{
			immune = true;
		}

	}

}

void CharacterKoopa::MoveLeft(float deltaTime)
{
	m_facing_direction = FACING_LEFT;
	m_position.x -= deltaTime * KOOPA_SPEED;
}

void CharacterKoopa::MoveRight(float deltaTime)
{
	m_facing_direction = FACING_RIGHT;
	m_position.x += deltaTime * KOOPA_SPEED;
}

void CharacterKoopa::AddGravity(float deltaTime)
{
	if (m_position.y + 40 <= SCREEN_HEIGHT)
	{
		m_position.y += GRAVITY * deltaTime;
		m_can_jump = false;
	}
	else
	{
		m_can_jump = true;
	}
}

void CharacterKoopa::FlipRightwayUp()
{

	if (m_facing_direction == FACING_RIGHT)
	{
		m_facing_direction = FACING_LEFT;
	}
	else
	{
		m_facing_direction = FACING_RIGHT;
	}

	m_injured = false;
	Jump();
}
