#pragma once
#include "FSMState.h"
class FSMState_Patrol :
    public FSMState
{
    FSMState_Patrol();
    ~FSMState_Patrol();
    FSMState* Update(Agent*, float);
    void Enter(Agent*, float);
    void Exit(Agent*,float);

};

