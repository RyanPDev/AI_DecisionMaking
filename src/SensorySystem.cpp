#include "SensorySystem.h"
#include "CoinBattleScene.h"
#include <iostream>
#include "utils.h"

using namespace Vector2DUtils;


SensorySystem::SensorySystem(Scene* _scene): scene(_scene)
{

}

SensorySystem::~SensorySystem()
{
}

void SensorySystem::Update(Agent* agent, float dTime)
{
	// Como pillamos los datos del player con una fordward declaration? <--- pregunta
	 
	if (Vector2D::Distance(scene->player->getPosition(),agent->getPosition()) < agent->blackBoard->GetSeeDistance()) // Calculate Distance between scene player and agent
	{
		if(Vector2DUtils::IsInsideCone(scene->player->getPosition(),
			agent->getPosition(),
			agent->getPosition() +(Vector2D::Normalize(agent->getVelocity()))* agent->blackBoard->GetSeeDistance(),
			agent->blackBoard->GetConeHalfAngle())) // Calculate if scene player inside cone
		{
			//std::cout << "I see you " << Vector2D::Distance(scene->player->getPosition(), agent->getPosition()) <<  std::endl;
			//if () // Calculate if there is no wall between scene player and agent
			{
				agent->blackBoard->SetPlayerInSight(true);
				agent->blackBoard->SetPlayerHasGun(scene->player->blackBoard->GetPlayerHasGun());
				
				
				agent->ChooseNewGoal(&pix2cell(scene->player->getPosition()));
				
				




				// CHANGE DESICION MAKING ALGORITHM

			}
		}
		

	}
	else
		agent->blackBoard->SetPlayerInSight(false);

	
	

}
