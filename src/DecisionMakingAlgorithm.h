#pragma once

class Agent;
class DecisionMakingAlgorithm
{
private:

public:
	DecisionMakingAlgorithm();
	~DecisionMakingAlgorithm();
	virtual void Update(Agent*, float) = 0;
};

