#include "FSM.h"
#include "Agent.h"

FSM::FSM()
{
}

FSM::~FSM()
{
}

void FSM::Update(Agent* _agent, float dtime)
{
	_agent->draw(true);
}
