#pragma once
#include "GameObjectManager.h"
#include <list>

#define TEXTURESIZEY 32
#define PLAYERTEXTUREY 38
#define GROUNDHEIGHT 150


//エネミー生成
class EnemyGenerateManager
{
public:
	EnemyGenerateManager();
	~EnemyGenerateManager();

	void Initialize(GameObjectManager *objectManager);
	void Update(float nowTime, int cannonCount);
private:
	void Generate(int cannonCnt);
private:

	GameObjectManager* m_pGameObjectManager;

	int cannonCount;
	std::list<float> _generateTime;
};

