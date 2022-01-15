#include "FSM.h"
#include "Agent.h"

void FSM::ChangeState(IFSMState* newState, Agent* agent, float dtime)
{
	//currentState->Exit(agent, dtime);
	//currentState = newState;
	//currentState->Enter(agent, dtime);
}

void FSM::Update(Agent* _agent, float dtime)
{
	//currentState->Update(_agent, dtime);
	_agent->draw(true);
}