#pragma once
#include "IFSMState.h"

class Chase :
	public IFSMState
{
private:
	float timer;
	const float MAX_TIMER{ 0.5 };

public:
	IFSMState* Update(Agent*, float);
	void Enter(Agent*, float);
	void Exit(Agent*, float);
	void ChooseNewGoal(Agent*);
};