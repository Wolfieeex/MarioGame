#pragma once
#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "Constants.h"

class Character;

class Collisions
{
private:

	Collisions();

	static Collisions* m_instance;

public:
	~Collisions();

	static Collisions* Instance();

	bool Circle(Circl2D circl1, Circl2D circl2);
	bool Box(Rect2D rect1, Rect2D rect2);

};

#endif