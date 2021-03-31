#pragma once
#ifndef ACCESSMANAGERS_H
#define ACCESSMANAGERS_H

#include "GameScreenManager.h"

class AccessManagers
{
public:
	GameScreenManager* m_global_screen_manager;

	void SetUpGlobalManager(GameScreenManager* manager) { m_global_screen_manager = manager; }
};

#endif