#pragma once
#include <iostream>

class Agent;

class IFSMState
{
public:

	virtual ~IFSMState()
	{
		std::cout << "entra";
		delete newState;
	}


	virtual IFSMState* Update(Agent*, float) = 0;
	virtual void Enter(Agent*, float dt = 0) = 0;
	virtual void Exit(Agent*, float dt = 0) = 0;
protected:
	IFSMState* newState;
};