#include "EnemyGenerateManager.h"
#include <fstream>
#include <sstream>
#include "Enemy.h"
#include "WindowInfo.h"


EnemyGenerateManager::EnemyGenerateManager()
{
}


EnemyGenerateManager::~EnemyGenerateManager()
{
}

void EnemyGenerateManager::Initialize(GameObjectManager *objectManager)
{
	m_pGameObjectManager = objectManager;
	//マップを読み込む
	std::ifstream ifs("data\\generateTime.csv");

	//ファイルの読み込みに成功したら
	if (ifs)
	{
		std::string s;
		while (!ifs.eof())
		{
			std::getline(ifs, s);
			_generateTime.push_back(atoi(s.c_str()));
		}
	}
}

void EnemyGenerateManager::Update(float nowTime, int cannonCnt)
{
	cannonCount = cannonCnt;
	if (_generateTime.empty())
	{
		return;
	}
	float time = _generateTime.front();
	if (time < nowTime)
	{
		Generate(cannonCount);
		_generateTime.pop_front();
	}
}

void EnemyGenerateManager::Generate(int cannonCnt)
{
	Vector2 generatePos = Vector2(
		GetRand(1) * WindowInfo::WindowWidth,
		WindowInfo::WindowHeight - GROUNDHEIGHT - PLAYERTEXTUREY - (GetRand(cannonCnt) * TEXTURESIZEY));

	
		m_pGameObjectManager->Add(new Enemy(generatePos, Vector2(1, 0)));
}