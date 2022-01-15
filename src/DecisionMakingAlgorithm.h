#pragma once

class Agent;
class DecisionMakingAlgorithm
{
private:

public:
	virtual void Update(Agent*, float) = 0;
};