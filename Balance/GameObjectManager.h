#pragma once
#include <vector>

class Object;
class Render;

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Update(float deltaTime);
	void Draw(Render* pRender);
	void Add(Object* pObject);

private:
	std::vector<Object*> mObjects;
};

