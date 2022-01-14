#include "SensorySystem.h"
#include "Scene.h"

SensorySystem::SensorySystem(Scene* _scene): scene(_scene)
{

}

SensorySystem::~SensorySystem()
{
}

void SensorySystem::Update(Agent* agent, float dTime)
{
	/*
	* // Como pillamos los datos del player con una fordward declaration? <--- pregunta
	* 
	if () // Calculate Distance between scene player and agent
	{
		if() // Calculate if scene player inside cone
		{
			if () // Calculate if there is no wall between scene player and agent
			{
				// CHANGE DESICION MAKING ALGORITHM

			}
		}
	}
	
	*/

}
