#include "GameScreenIntro.h"
#include <iostream>
#include "Texture2D.h"

using namespace std;

GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenIntro::~GameScreenIntro()
{
	delete m_background_texture;
	m_background_texture = nullptr;
}

void GameScreenIntro::Render()
{
	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

}

void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{

}

bool GameScreenIntro::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
	else
	{
		return true;
	}
}