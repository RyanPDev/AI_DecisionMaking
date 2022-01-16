#pragma once
class IFSMState;
class Agent;

class DecisionMakingAlgorithm
{
public:
	virtual void Update(Agent*, float) = 0;
};