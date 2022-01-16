#pragma once
#include "IFSMState.h"

class Patrol :
    public IFSMState
{
private:
    void EvadeOtherAgent(Agent* agent, int i);
    void ChooseNewGoal(Agent* agent);
public:
    IFSMState* Update(Agent*, float);
    void Enter(Agent*, float);
    void Exit(Agent*,float);
};