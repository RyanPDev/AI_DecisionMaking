
class Agent;
class Scene;
#pragma once
class SensorySystem
{
private:
	Scene* scene;

public:
	SensorySystem(Scene*);
	~SensorySystem();

	void Update(Agent* agent, float dTime);

};

