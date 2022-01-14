#pragma once
#include "FSMState.h"
class FSMState_Evade :
    public FSMState
{
    FSMState_Evade();
    ~FSMState_Evade();
    FSMState* Update(Agent*, float);
    void Enter(Agent*, float);
    void Exit(Agent*, float);
};

