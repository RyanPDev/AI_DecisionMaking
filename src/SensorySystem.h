#pragma once
class Agent;
class Scene;
#pragma once
class SensorySystem
{
private:

public:
	SensorySystem(Scene*);
	~SensorySystem();

	void Update(Agent* agent, float dTime);
	Scene* scene;
};