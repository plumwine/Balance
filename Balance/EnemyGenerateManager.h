#pragma once
#include "GameObjectManager.h"
#include <list>

#define TEXTURESIZEY 90
#define CANNONTEXTURESIZEY 96
#define PLAYERTEXTUREY 128
#define GROUNDHEIGHT 144
#define THISTEXTURESIZEY 32


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
	void Generate(int cannonCnt,int R0L1);
private:

	GameObjectManager* m_pGameObjectManager;

	int cannonCount;
	std::list <float> _generateTime;
};

