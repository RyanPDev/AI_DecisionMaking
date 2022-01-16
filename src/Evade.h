#pragma once
#include "IFSMState.h"

class Evade :
    public IFSMState
{
private:
    float timer;
    const float MAX_TIMER{ .5 };

public:
    IFSMState* Update(Agent*, float);
    void Enter(Agent*, float);
    void ChooseNewGoal(Agent* agent);
    void Exit(Agent*, float);
};