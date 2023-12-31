﻿#pragma once
#include <vector>
#include "GameState.h"

class StateMachine
{
public:
	static void addState(GameState* pState);
	static void switchState(GameState* pState);

	void Render();
	void Update();

	void KillAllStates();
	void killState();
	 
private:

	 static GameState* sGameState; // trạng thái của chương trình 
	 // static std::vector<GameState*> GameState_Vector;

};

