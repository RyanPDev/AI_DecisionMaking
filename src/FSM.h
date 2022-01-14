#pragma once
#include "DecisionMakingAlgorithm.h"
class FSM :
    public DecisionMakingAlgorithm
{
private:
public:
    FSM();
    ~FSM();
   void Update(Agent*,float);
};

