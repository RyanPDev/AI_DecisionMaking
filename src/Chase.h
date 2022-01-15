#pragma once
#include "IFSMState.h"

class Chase :
	public IFSMState
{
public:
	IFSMState* Update(Agent*, float);
	void Enter(Agent*, float);
	void Exit(Agent*, float);

};