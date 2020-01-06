#pragma once
#include "GameObjectManager.h"
#include <vector>



enum StageWave
{
	Stage1,
	Stage2,
	Stage3
};

//	ゲームプレイ管理クラス
class GamePlayManager
{
private:
	GamePlayManager() { Initialize(); }
	GamePlayManager(const GamePlayManager&) { Initialize(); }
	GamePlayManager& operator=(const GamePlayManager&) {}
public:

	//	インスタンスを取得
	static GamePlayManager& Instance();

	void Initialize(); //初期化

	//	ループ処理
	void Update(float deltaTime);

	//  更新処理
	void GameUpdate(float deltaTime);

	//Wave
	void WaveUpdate(float deltaTime);

	//ウェイブ管理
	void Wave_1(float deltaTime);
	void Wave_2(float deltaTime);
	void Wave_3(float deltaTime);
	void ChangeWave(StageWave wave);

	void EnemyDeadCountUp() { enemyDeadCount++; };       //敵死亡カウントUP
	void EnemyDeadCountDown() { enemyDeadCount--; };     //敵死亡カウントDOWN
	

private:
	
	std::vector<int> cannonCount;
	StageWave nowSatge;
	int enemyDeadCount;                  //敵死亡カウント兼大砲生成カウント
	GameObjectManager m_pGameManager;    //ゲームオブジェクトマネージャー
};