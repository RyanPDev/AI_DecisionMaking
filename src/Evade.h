#pragma once
#include "IFSMState.h"

class Evade :
    public IFSMState
{
private:
    float timer;
    const float MAX_TIMER{ .5 };
    void ChooseNewGoal(Agent* agent);
    void EvadePlayer(Agent* agent);

public:
    IFSMState* Update(Agent*, float);
    void Enter(Agent*, float);
    void Exit(Agent*, float);
};