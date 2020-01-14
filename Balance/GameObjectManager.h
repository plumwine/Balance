#pragma once
#include <vector>
#include "Object.h"

class GameObjectManager
{
public:
	GameObjectManager();


	~GameObjectManager();

	void Update(float deltaTime);
	void Draw();
	void Add(Object* pObject);
	void enemyDir();
	float TopCannon();

private:
	std::vector<Object*> mObjects;
	std::vector<Object*> m_addObjectList;
};

