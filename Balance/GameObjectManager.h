#pragma once
#include <vector>

class Object;

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Update(float deltaTime);
	void Draw();
	void Add(Object* pObject);

private:
	std::vector<Object*> mObjects;
};

