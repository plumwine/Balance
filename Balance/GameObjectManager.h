#pragma once
#include <vector>
#include "Object.h"

class GameObjectManager
{
public:
	GameObjectManager();


	~GameObjectManager();

	void Clear();
	void Update(float deltaTime);
	void Draw();
	void Add(Object* pObject);
	void enemyDir();
	float TopCannon();

private:
	std::vector<Object*> mObjects;
	std::vector<Object*> m_addObjectList;
	std::vector<Object*> m_Cannon;         //íeä«óù
	std::vector<Object*> m_enemy;          //ìGä«óù
};

