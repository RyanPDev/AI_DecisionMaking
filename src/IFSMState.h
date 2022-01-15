#pragma once

class Agent;

class IFSMState
{
public:
	virtual ~IFSMState() {}

	virtual IFSMState* Update(Agent*, float) = 0;
	virtual void Enter(Agent*, float) = 0;
	virtual void Exit(Agent*, float) = 0;
};