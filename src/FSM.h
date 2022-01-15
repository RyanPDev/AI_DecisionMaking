#pragma once
#include "DecisionMakingAlgorithm.h"
#include "IFSMState.h"

class FSM :
	public DecisionMakingAlgorithm
{
private:
	IFSMState* currentState;

	void ChangeState(IFSMState*, Agent*, float);

public:
	void Update(Agent*, float);
};