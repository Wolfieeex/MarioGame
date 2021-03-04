#pragma once
#ifndef CHARACTERCOIN_H
#define CHARACTERCOIN_H

#include "Character.h"

class CharacterCoin : public Character
{
private:
	float m_movement_speed;
	float m_single_sprite_w;
	float m_single_sprite_h;
	int m_current_frame;
	float m_animation_transition;
	bool m_collected;

public:
	CharacterCoin(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D start_position);
	~CharacterCoin() {};

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void AddGravity(float deltaTime) override {};
	void FlipCoin();
	bool GetCollected() { return m_collected; }
	void SetCollected() { m_collected = true; }
};

#endif

