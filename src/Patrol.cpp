#include "Patrol.h"
#include "Agent.h"
#include "utils.h"
#include "Scene.h"

IFSMState* Patrol::Update(Agent* agent, float dtime)
{
	//Checks distance between agents. If they're close enough, start modifiying weights around them so they can evade each other
	int i = 0;
	if (agent->sensors->scene->agents[0] == agent)
		i = 1;
	if (CalculateDistance(agent->getPosition(), agent->sensors->scene->agents[i]->getPosition()) < agent->blackBoard->GetEvasiveDistance())
	{
		agent->blackBoard->graph.ResetAllWeights();
		agent->blackBoard->graph.ChangeWeights(agent->sensors->scene->agents[i]->getPosition(), 100000, 20000, 10000);
		agent->ChooseNewGoal();

		
	}

	if (pix2cell(agent->getPosition()) == *agent->currentGoal)
	{
		agent->ChooseNewGoal();
		agent->blackBoard->graph.ResetAllWeights();
		
	}
	return nullptr;
}

void Patrol::Enter(Agent* agent, float dtime)
{
	agent->ChooseNewGoal();
	agent->blackBoard->graph.ResetAllWeights();

}

void Patrol::Exit(Agent*, float)
{
}