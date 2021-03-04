#pragma once
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 412
#define MOVEMENTSPEED 150.0f
#define GRAVITY 250.0f
#define JUMP_FORCE_DECREMENT 400.0f
#define INITIAL_JUMP_FORCE 600.0f
#define MAP_HEIGHT 13
#define MAP_WIDTH 16
#define TILE_WIDTH 32
#define TILE_HEIGHT 32
#define SHAKE_DURATION 0.25f
#define INJURED_TIME 2.5F
#define INITIAL_JUMP_FORCE_SMALL 300.0f
#define INITIAL_JUMP_FORCE_ENEMY 450.0f
#define INJURE_COOLDOWN 0.2F
#define KOOPA_SPEED 62.0f
#define SPAWN_COOLDOWN 15.0F
#define ANIMATION_COOLDOWN 0.1F
#define WALKING_ANIMATION_COOLDOWN 0.5F;
#define GOOMBA_SPEED 40.0f


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

