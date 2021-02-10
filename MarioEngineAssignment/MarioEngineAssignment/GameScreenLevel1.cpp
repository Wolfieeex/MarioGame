#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
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
		//set up player character
		my_mario_character = new MarioCharacter(m_renderer, "Images/Mario.png", Vector2D(64, 342));
		my_luigi_character = new LuigiCharacter(m_renderer, "Images/Luigi.png", Vector2D(300, 342));
		return true;
	}
}