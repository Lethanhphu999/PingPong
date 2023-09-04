#include "StateMachine.h"

GameState* StateMachine::sGameState = nullptr;
void StateMachine::addState(GameState* state) {
//	printf("HELLO");
	sGameState = state;
	sGameState->onEnter();
}

void StateMachine::killState() {
	if (sGameState) {
		if (sGameState->onExit())
		{ 
		    sGameState = NULL;
		}
	}
}

void StateMachine::Render()
{
	if (sGameState)
	{ 
		sGameState->Render();
	}
}
/*
Update trạng thái của chương trình thông qua Interface 
*/
void StateMachine::Update()
{
	if (sGameState) 
	{ 
		sGameState->Update();
	}
}

void StateMachine::switchState(GameState* state) {
	if (sGameState) {

		sGameState->onExit();
		sGameState=  NULL;
		
	}
	sGameState = state;
	sGameState->onEnter();

}

void StateMachine::KillAllStates() {
	if (sGameState) {
		
		sGameState->onExit();
		sGameState = NULL;

	//	GameState_Vector.clear(); //Kills every stored state
	//	GameState_Vector.shrink_to_fit(); // Sets capacity back to 0
		
	}

}