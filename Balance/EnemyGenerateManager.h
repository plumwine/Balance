#pragma once
#include "GameObjectManager.h"
#include <vector>

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
	//文字列の分割を行う
	std::vector<float> Split(const std::string& str, char delim = ',');
private:

	GameObjectManager* m_pGameObjectManager;

	int cannonCount;
	std::vector < std::vector<float>> _generateTime;
	std::vector < std::vector<float>>::iterator _generateItr;

	std::vector<float> _generate;

	bool generateFlag;
};

