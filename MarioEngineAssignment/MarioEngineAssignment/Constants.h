#pragma once
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 412
#define MOVEMENTSPEED 150.0f
#define GRAVITY 250.0f
#define JUMP_FORCE_DECREMENT 400.0f
#define INITIAL_JUMP_FORCE 600.0f

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float initial_x, float initial_y)
	{
		x = initial_x;
		y = initial_y;
	}
};

struct Rect2D
{
	float x;
	float y;
	float width;
	float height;

	Rect2D(float x_pos, float y_pos, float width, float height)
	{
		x = x_pos;
		y = y_pos;
		this->width = width;
		this->height = height;
	}
};

struct Circl2D
{
	float x;
	float y;
	float radius;
	Circl2D(float x_pos, float y_pos, float radius)
	{
		x = x_pos;
		y = y_pos;
		this->radius = radius;
	}
};

enum FACING
{
	FACING_LEFT,
	FACING_RIGHT
};


enum SCREENS
{
	SCREEN_INTRO,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

