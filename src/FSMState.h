#pragma once

class Agent;

class FSMState
{
public:
	FSMState();
	~FSMState();
	virtual FSMState* Update(Agent*, float) = 0;
	virtual void Enter(Agent*, float) = 0;
	virtual void Exit(Agent*, float) = 0;
};

