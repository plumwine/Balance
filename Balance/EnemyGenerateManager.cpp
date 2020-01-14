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
	//ƒ}ƒbƒv‚ğ“Ç‚İ‚Ş
	std::ifstream ifs("data\\generateTime.csv");

	//ƒtƒ@ƒCƒ‹‚Ì“Ç‚İ‚İ‚É¬Œ÷‚µ‚½‚ç
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
	///ƒ‰ƒ“ƒ_ƒ€(0`ˆø”‚Ì”šŠÜ‚Ş”)()‚Ì’†‚Æ‰º‚Ì¶‚©‚ç‚Ì“G‚Ì”äŠr‰‰Zq‚Ì‰E•Ó‚Ì”’l‚ğ•Ï‚¦‚é‚±‚Æ‚Å”ä—¦‚ğ•ÏX‚Å‚«‚é
	int randSpawnX = GetRand(5);

	//¶‚©‚ç”­Ë‚³‚ê‚é“G
	if (randSpawnX <= 1)
	{
		Vector2 generatePos = Vector2(
			0,
			WindowInfo::WindowHeight - GROUNDHEIGHT - PLAYERTEXTUREY - (GetRand(cannonCnt) * TEXTURESIZEY));
		m_pGameObjectManager->Add(new Enemy(generatePos, Vector2(1, 0)));
	}
	//‰E‚©‚ç”­Ë‚³‚ê‚é“G
	else
	{
		Vector2 generatePos = Vector2(
			WindowInfo::WindowWidth,
			WindowInfo::WindowHeight - GROUNDHEIGHT - PLAYERTEXTUREY - (GetRand(cannonCnt) * TEXTURESIZEY));
		m_pGameObjectManager->Add(new Enemy(generatePos, Vector2(-1, 0)));
	}
}