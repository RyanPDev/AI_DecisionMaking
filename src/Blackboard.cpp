#include "Blackboard.h"

Blackboard::Blackboard(Graph _graph): graph(_graph)
{
	seeDistance = 10; // also for cone
	coneAngle = 30;
	playerInSight = false;
	playerHasGun = false;
}

Blackboard::~Blackboard() {

}