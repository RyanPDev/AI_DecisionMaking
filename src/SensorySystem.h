#pragma once
class Agent;
class Scene;
#pragma once
class SensorySystem
{
private:
	bool LineTrace(Agent* agent);

public:
	SensorySystem(Scene*);

	void Update(Agent* agent, float dTime);
	Scene* scene;
};