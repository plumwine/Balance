#pragma once
#include "GameObjectManager.h"

//エネミー生成
class EnemyGenerateManager
{
public:
	EnemyGenerateManager(GameObjectManager *objectManager);
	~EnemyGenerateManager();

	void Update(float deltaTime);
private:
	void Generate(float deltaTime);

private:

	GameObjectManager* m_pGameObjectManager;
};

