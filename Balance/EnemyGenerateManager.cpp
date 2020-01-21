#include "EnemyGenerateManager.h"
#include <fstream>
#include <sstream>
#include "Enemy.h"
#include "WindowInfo.h"
#include "GamePlayManager.h"


EnemyGenerateManager::EnemyGenerateManager()
{
}


EnemyGenerateManager::~EnemyGenerateManager()
{
}

void EnemyGenerateManager::Initialize(GameObjectManager *objectManager)
{
	generateFlag = true;

	m_pGameObjectManager = objectManager;
	//マップを読み込む
	std::ifstream ifs("data\\generateTime.csv");

	//ファイルの読み込みに成功したら
	
	if (ifs)
	{
		//文字列を一行ずつ読み込む
		std::string line;
		while (getline(ifs, line))
		{
			//読み込んだ文字列をカンマ区切りで分割
			std::vector<float> data = Split(line);

			//マップ情報を格納
			_generateTime.push_back(data);
		}

		_generateItr = _generateTime.begin();

		_generate = *_generateItr;
	}
}

void EnemyGenerateManager::Update(float nowTime, int cannonCnt)
{
	cannonCount = cannonCnt;

	if (cannonCount == 0 || _generateTime.empty() || !generateFlag)
	{
		return;
	}

	auto itr = _generate.begin();

	if (*itr > nowTime)
	{
		return;
	}

	itr++;
	if (_generate.size() == 2)
	{
		for (auto i = 0; i < *itr; i++)
		{
			Generate(cannonCount);
		}
	}



	if (_generateItr == _generateTime.end())
	{
		generateFlag = false;
		return;
	}

	_generateItr++;
	_generate = *_generateItr;
}

void EnemyGenerateManager::Generate(int cannonCnt)
{
	///ランダム(0〜引数の数字含む数)()の中と下の左からの敵の比較演算子の右辺の数値を変えることで比率を変更できる
	int randSpawnX = GetRand(5);

	//左から発射される敵
	if (randSpawnX <= 1)
	{
		Vector2 generatePos = Vector2(
			0,
			WindowInfo::WindowHeight - GROUNDHEIGHT - PLAYERTEXTUREY - ((GetRand(cannonCnt - 1) + 1) * CANNONTEXTURESIZEY) + (CANNONTEXTURESIZEY / 2 - THISTEXTURESIZEY / 2));
		m_pGameObjectManager->Add(new Enemy(generatePos, Vector2(1, 0), GamePlayManager::Instance().GetWave()));
	}
	//右から発射される敵
	else
	{
		Vector2 generatePos = Vector2(
			WindowInfo::WindowWidth,
			WindowInfo::WindowHeight - GROUNDHEIGHT - PLAYERTEXTUREY - ((GetRand(cannonCnt - 1) + 1) * CANNONTEXTURESIZEY) + (CANNONTEXTURESIZEY / 2 - THISTEXTURESIZEY / 2));
		m_pGameObjectManager->Add(new Enemy(generatePos, Vector2(-1, 0),GamePlayManager::Instance().GetWave()));
	}
}

void EnemyGenerateManager::Generate(int cannonCnt, int R0L1)
{
	//左から発射される敵
	if (R0L1 == 1)
	{
		Vector2 generatePos = Vector2(
			0,
			//　画面縦幅　　　　　　 - 　地面の高さ - プレイヤーの高さ - ランダムの砲台の位置        *  砲台の高さ         +  （砲台の高さ　/　2　-　敵の高さ　/　2）　←座標合わせのあとの中心合わせ
			WindowInfo::WindowHeight - GROUNDHEIGHT - PLAYERTEXTUREY - ((GetRand(cannonCnt - 1) + 1) * CANNONTEXTURESIZEY) + (CANNONTEXTURESIZEY / 2 - THISTEXTURESIZEY / 2));
		m_pGameObjectManager->Add(new Enemy(generatePos, Vector2(1, 0), GamePlayManager::Instance().GetWave()));
	}
	//右から発射される敵
	else
	{
		Vector2 generatePos = Vector2(
			WindowInfo::WindowWidth,
			WindowInfo::WindowHeight - GROUNDHEIGHT - PLAYERTEXTUREY - ((GetRand(cannonCnt - 1) + 1) * CANNONTEXTURESIZEY) + (CANNONTEXTURESIZEY / 2 - THISTEXTURESIZEY / 2));
		m_pGameObjectManager->Add(new Enemy(generatePos, Vector2(-1, 0), GamePlayManager::Instance().GetWave()));
	}
}


std::vector<float> EnemyGenerateManager::Split(const std::string & str, char delim)
{
	//文字列操作を行うため文字列ストリームを宣言
	std::stringstream iss(str);
	std::string tmp;
	std::vector<float> enemyRow;

	//文字列をカンマ区切りで読み込む
	while (getline(iss, tmp, delim))
	{//atoi->文字列を数字に
		enemyRow.push_back(std::atoi(tmp.c_str()));
	}

	return enemyRow;
}
