#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D start_position) : Character(renderer, imagePath, start_position, map)
{
	m_collected = false;
	m_animation_transition = ANIMATION_COOLDOWN;

	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
}

void CharacterCoin::Render()
{
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame, 0,m_single_sprite_w, m_single_sprite_h };

	m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
}

void CharacterCoin::Update(float deltaTime, SDL_Event e)
{
	m_animation_transition -= deltaTime;

	if (m_animation_transition <= 0)
	{
		if (m_current_frame != 2)
		{
			m_animation_transition = ANIMATION_COOLDOWN;
			m_current_frame++;
		}
		else
		{
			m_animation_transition = ANIMATION_COOLDOWN;
			m_current_frame = 0;
		}
	}
}

void CharacterCoin::FlipCoin()
{
}
