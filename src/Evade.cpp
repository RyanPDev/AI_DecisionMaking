#include "Evade.h"
#include "Chase.h"
#include "Patrol.h"
#include "Agent.h"
#include "Scene.h"

IFSMState* Evade::Update(Agent* agent, float dtime)
{
	timer -= dtime;

	//UPDATE GOAL WHILE BEING CHASED
	if (Vector2D::Distance(agent->currentGoal, Vector2D::pix2cell(agent->getPosition())) < 150 ||
		Vector2D::Distance(agent->sensors->scene->player->getPosition(), agent->getPosition()) < agent->blackBoard->GetSeeDistance() * 0.6)
	{
		ChooseNewGoal(agent);
	}

	if (timer <= 0)
	{
		timer = MAX_TIMER; //--> Timer to make evading timing irregular to the user eyes, also works as to not do this calculations every frame

		//If player is not in sight, change back to Patrol state
		if (!agent->blackBoard->GetPlayerInSight())
		{
			delete newState;
			newState = new Patrol();
			return newState;
		}

		//If player hasn't got a gun anymore, change back to Chase state
		if (!agent->blackBoard->GetPlayerHasGun())
		{
			delete newState;
			newState = new Chase();
			return newState;
		}
	}
	return nullptr;
}

//SETS INITIAL GOAL TO EVADE TO
void Evade::Enter(Agent* agent, float dtime)
{
	timer = 0;
	agent->setMaxVelocity(280); //Increments movement speed while evading

	ChooseNewGoal(agent);
}

//CALCULATES A NEW GOAL WITH A DOT PRODUCT BETWEEN VECTOR FROM PLAYER-ENEMY AND VECTOR FROM GOAL-ENEMY
//THIS WAY THE NEW GOAL WILL ALWAYS BE SOMEWHAT IN THE OPPOSITE DIRECTION OF THE PLAYER WHOM THE AGENT IS TRYING TO EVADE
void Evade::ChooseNewGoal(Agent* agent) // Checks if the new goal is not behind the player respect the enemy
{
	int counter = 0;
	Vector2D a;
	Vector2D b;

	agent->blackBoard->graph.ChangeWeights(agent->sensors->scene->player->getPosition(), 100000, 20000, 10000);

	b = Vector2D::Normalize(agent->sensors->scene->player->getPosition() - agent->getPosition());

	do
	{
		agent->ReplaceWanderPosition();
		counter++;
		a = Vector2D::Normalize(agent->currentGoal - Vector2D::pix2cell(agent->getPosition()));
	} while (Vector2D::Dot(a, b) > 0.5 && counter < 30);

	agent->RecalculatePath();

	if (counter >= 30)
	{
		agent->ChooseNewGoal(); //--> Chooses random new Goal if within 30 tries cannot find a better one
	}
}

void Evade::Exit(Agent* agent, float dtime)
{
	agent->setMaxVelocity(180); //Reset to default speed after evading successfully
}