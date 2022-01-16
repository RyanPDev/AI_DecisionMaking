#pragma once
#include "IFSMState.h"

class Patrol :
    public IFSMState
{
public:
    IFSMState* Update(Agent*, float);
    void ChooseNewGoal(Agent* agent);
    void Enter(Agent*, float);
    void Exit(Agent*,float);
};