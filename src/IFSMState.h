#pragma once
#include <iostream>

class Agent;

class IFSMState
{
public:

    virtual ~IFSMState()
    {
        delete newState;
    }

    virtual IFSMState* Update(Agent*, float) = 0;
    virtual void Enter(Agent*, float dt = 0) = 0;
    virtual void Exit(Agent*, float dt = 0) = 0;
protected:
    IFSMState* newState;
    virtual void ChooseNewGoal(Agent*) = 0;
};