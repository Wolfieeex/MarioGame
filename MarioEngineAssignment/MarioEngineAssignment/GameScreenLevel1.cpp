#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
#include "LevelMap.h"

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_level_map = nullptr;
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	delete my_mario_character;
	delete my_luigi_character;
	m_background_texture = nullptr;
	my_mario_character = nullptr;
	my_luigi_character = nullptr;
}

void GameScreenLevel1::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	my_mario_character->Render();
	my_luigi_character->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//update character
	if (Collisions::Instance()->Box(my_mario_character->GetCollisionBox(), my_luigi_character->GetCollisionBox()))
	{
		cout << "Box hit!" << endl;
	}

	if (Collisions::Instance()->Circle(my_mario_character->GetCollisionCircle(), my_luigi_character->GetCollisionCircle()))
	{
		cout << "Circle hit!" << endl;
	}

	my_mario_character->Update(deltaTime, e);
	my_luigi_character->Update(deltaTime, e);

}

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

		//set up player character
		my_mario_character = new MarioCharacter(m_renderer, "Images/Mario.png", Vector2D(64, 332), m_level_map);
		my_luigi_character = new LuigiCharacter(m_renderer, "Images/Luigi.png", Vector2D(300, 332), m_level_map);

		return true;
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
