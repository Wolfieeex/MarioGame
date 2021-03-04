#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include "CharacterGoomba.h"
#include <ctime>

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	srand(time(NULL));
	m_enemy_spawn_cooldown = SPAWN_COOLDOWN;
	m_level_map = nullptr;
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	delete my_mario_character;
	delete my_luigi_character;
	delete m_pow_block;

	m_background_texture = nullptr;
	my_mario_character = nullptr;
	my_luigi_character = nullptr;
	m_pow_block = nullptr;

	m_enemies.clear();
	m_coins.clear();
	m_enemies_goomba.clear();
}

void GameScreenLevel1::Render()
{
	//draw the enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}

	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render();
	}

	for (int i = 0; i < m_enemies_goomba.size(); i++)
	{
		m_enemies_goomba[i]->Render();
	}

	//draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	my_mario_character->Render();
	my_luigi_character->Render();
	m_pow_block->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}

	UpdateEnemies(deltaTime, e);
	UpdateCoins(deltaTime, e);
	UpdatePOWBlock();

	my_mario_character->Update(deltaTime, e);
	my_luigi_character->Update(deltaTime, e);

	m_enemy_spawn_cooldown -= deltaTime;

	if (m_enemy_spawn_cooldown <= 0)
	{
		int random;
		random = rand() % 2;
		switch (random)
		{
		case 0:
			CreateKoopa(Vector2D((rand() % 175) + 150, 32), FACING_RIGHT, KOOPA_SPEED);
			m_enemy_spawn_cooldown = SPAWN_COOLDOWN;
			break;
		case 1:
			CreateKoopa(Vector2D((rand() % 175) + 150, 32), FACING_LEFT, KOOPA_SPEED);
			m_enemy_spawn_cooldown = SPAWN_COOLDOWN;
			break;
		default:
			break;
		}
		
	}
}

void GameScreenLevel1::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(my_mario_character->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			//collided while jumping
			if (my_mario_character->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				my_mario_character->CancelJump();
			}

		}
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			m_enemies[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->
				GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i]->GetCollisionCircle(), my_mario_character->GetCollisionCircle()))
				{
					if (my_mario_character->IsInAir())
					{
						my_mario_character->EnemyJump(deltaTime, INITIAL_JUMP_FORCE_ENEMY);
						m_enemies[i]->TakeDamage();
					}
					else
					{
						my_mario_character->SetAlive(false);
					}

				}
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//remove dead enemies -1 each update

		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}


	if (!m_enemies_goomba.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies_goomba.size(); i++)
		{
			m_enemies_goomba[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_enemies_goomba[i]->GetPosition().y > 300.0f || m_enemies_goomba[i]->GetPosition().y <= 64.0f) && (m_enemies_goomba[i]->
				GetPosition().x < 64.0f || m_enemies_goomba[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies_goomba[i]->GetCollisionCircle(), my_mario_character->GetCollisionCircle()))
				{
					if (my_mario_character->IsInAir())
					{
						my_mario_character->EnemyJump(deltaTime, INITIAL_JUMP_FORCE_ENEMY);
						m_enemies_goomba[i]->TakeDamage();
					}
					else
					{
						my_mario_character->SetAlive(false);
					}

				}
			}

			//if the enemy is no longer alive then schedule it for deletion
			if (!m_enemies_goomba[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//remove dead enemies -1 each update

		if (enemyIndexToDelete != -1)
		{
			m_enemies_goomba.erase(m_enemies_goomba.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (!m_coins.empty())
	{
		int coinIndexToDelete = -1;
		for (unsigned int i = 0; i < m_coins.size(); i++)
		{
			m_coins[i]->Update(deltaTime, e);

			if (Collisions::Instance()->Circle(m_coins[i]->GetCollisionCircle(), my_mario_character->GetCollisionCircle()))
			{
				my_mario_character->AddPoints();
				m_coins[i]->SetCollected();
			}

			if (m_coins[i]->GetCollected())
			{
				coinIndexToDelete = i;
			}
		}
		if (coinIndexToDelete != -1)
		{
			m_coins.erase(m_coins.begin() + coinIndexToDelete);
		}
	}

}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	m_enemies.push_back(new CharacterKoopa(m_renderer, "Images/Koopa.png", m_level_map, position, direction, speed));
}

void GameScreenLevel1::CreateCoin(Vector2D position)
{
	m_coins.push_back(new CharacterCoin(m_renderer, "Images/Coin.png", m_level_map, position));
}

void GameScreenLevel1::CreateGoomba(Vector2D position, float speed)
{
	m_enemies_goomba.push_back(new CharacterGoomba(m_renderer, "Images/Goomba.png", m_level_map, position, speed));
}
;

bool GameScreenLevel1::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
	else
	{
		SetLevelMap();

		CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

		CreateGoomba(Vector2D(150, 200), KOOPA_SPEED);
		CreateGoomba(Vector2D(325, 200), KOOPA_SPEED);
		CreateGoomba(Vector2D(230, 100), KOOPA_SPEED);

		CreateCoin(Vector2D(250, 120));
		CreateCoin(Vector2D(137, 120));
		CreateCoin(Vector2D(360, 120));

		//set up player character
		my_mario_character = new MarioCharacter(m_renderer, "Images/Mario.png", Vector2D(64, 332), m_level_map);
		my_luigi_character = new LuigiCharacter(m_renderer, "Images/Luigi.png", Vector2D(300, 332), m_level_map);

		m_pow_block = new PowBlock(m_renderer, m_level_map);
		m_screenshake = false;
		m_background_yPos = 0.0f;

		return true;
	}
}

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
									   { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									   { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };


	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);

}
