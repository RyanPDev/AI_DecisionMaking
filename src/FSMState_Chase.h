#pragma once
#include "FSMState.h"
class FSMState_Chase :
    public FSMState
{
    FSMState_Chase();
    ~FSMState_Chase();
    FSMState* Update(Agent*, float);
    void Enter(Agent*, float);
    void Exit(Agent*, float);

};

