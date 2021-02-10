#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>

//Files included
#include "Constants.h"
#include "Texture2D.h"
#include "GameScreenManager.h"

//Namespace
using namespace std;

//Function prototypes
bool Update();
bool InitSDL();
void CLoseSDL();
void Render();


//Global variables
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;

double rotation = NULL;
SDL_RendererFlip flip;

int main(int argc, char* args[])
{
	rotation = 0;
	flip = SDL_FLIP_NONE;

	//check if sdl was setup correctly
	if (InitSDL())
	{
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_INTRO);
		//set the time
		g_old_time = SDL_GetTicks();

		//flag to check if we wish to quit
		bool quit = false;

		//Game Loop
		while (!quit)
		{
			Render();
			quit = Update();
		}

	}
	CLoseSDL();

	return 0;
}

bool InitSDL()
{
	//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//setup passed so create window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//did the window get created?
		if (g_window == nullptr)
		{
			//window failed
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
		else
		{
			g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
			if (g_renderer != nullptr)
			{
				//init PNG loading
				int imageFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imageFlags) & imageFlags))
				{
					cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
					return false;
				}
				else
				{
					return true;
				}
			}
			else
			{
				cout << "Renderer could not initialise. Error: " << SDL_GetError();
				return false;
			}
		}
	}
}

void CLoseSDL()
{
	//destroy the game screen manager
	delete game_screen_manager;
	game_screen_manager = nullptr;

	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;

	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	//release the renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;
}
bool Update()
{
	Uint32 new_time = SDL_GetTicks();

	//Event handler
	SDL_Event e;

	//get events
	SDL_PollEvent(&e);

	//handle the events
	switch (e.type)
	{
		//click the 'X' to quit
	case SDL_QUIT:
		return true;
		break;
	case SDL_MOUSEBUTTONDOWN:
		return true;
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_q:
			return true;
			break;
		case SDLK_r:
			rotation += 5;
			return false;
			break;
		case SDLK_z:
			game_screen_manager->ChangeScreen(SCREEN_LEVEL1);
			return false;
			break;
		case SDLK_0:
			flip = SDL_FLIP_NONE;
			return false;
			break;
		case SDLK_1:
			flip = SDL_FLIP_HORIZONTAL;
			return false;
			break;
		case SDLK_2:
			flip = SDL_FLIP_VERTICAL;
			return false;
			break;
		}
	}
	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;

	return false;
}

void Render()
{
	//Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);

	game_screen_manager->Render();

	//update the screen
	SDL_RenderPresent(g_renderer);

}
