#pragma once
#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <SDL.h>
#include <string>
#include "Constants.h"

class Texture2D
{

public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	bool LoadFromFile(std::string path);
	void Free();
	void Render(Vector2D new_position, SDL_RendererFlip flip, double angle = 0.0);

	int GetWidth() { return m_width; }
	int GetHeight() { return  m_height; }

	void Render(SDL_Rect src_rect, SDL_Rect src_dest, SDL_RendererFlip flip, double angle = 0.0);

private:
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;

	int m_width;
	int m_height;


};

#endif 
