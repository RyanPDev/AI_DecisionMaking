#include "Patrol.h"
#include "Agent.h"
#include "utils.h"
#include "Scene.h"
#include "Chase.h"

IFSMState* Patrol::Update(Agent* agent, float dtime)
{
	//Checks distance between agents. If they're close enough, start modifiying weights around them so they can evade each other
	int i = 0;
	if (agent->sensors->scene->agents[0] == agent) i = 1;

	if (CalculateDistance(agent->getPosition(), agent->sensors->scene->agents[i]->getPosition()) < agent->blackBoard->GetEvasiveDistance())
	{
		
		agent->blackBoard->graph.ResetAllWeights();
		agent->blackBoard->graph.ChangeWeights(agent->sensors->scene->agents[i]->getPosition(), 100000, 20000, 10000);
		ChooseNewGoal(agent);
	}

	if (pix2cell(agent->getPosition()) == agent->currentGoal)
	{
		ChooseNewGoal(agent);
		agent->blackBoard->graph.ResetAllWeights();
	}

	if (agent->blackBoard->GetPlayerInSight())
	{
		delete newState;
		newState = new Chase();
		return newState;
	}

	return nullptr;
}
void Patrol::ChooseNewGoal(Agent* agent)
{
	Vector2D a;
	Vector2D b;
	int counter = 0;
	b = Vector2D::Normalize(agent->getVelocity());
	do
	{
		agent->ReplaceWanderPosition();
		a = Vector2D::Normalize(agent->currentGoal - pix2cell(agent->getPosition()));
		counter++;
	} while (Vector2D::Dot(a, b) < 0 && counter < 30);

	agent->RecalculatePath();

	if (counter >= 30)
	{
		agent->ChooseNewGoal();
	}
}

void Patrol::Enter(Agent* agent, float dtime)
{
	agent->blackBoard->graph.ResetAllWeights();
}

void Patrol::Exit(Agent* agent, float dtime)
{
	agent->blackBoard->graph.ResetAllWeights();
}