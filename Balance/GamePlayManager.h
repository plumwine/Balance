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
	void Update();

	//  更新処理
	void GameUpdate(float deltaTime);
	void EnemyDeadCountUp() { enemyDeadCount++; };       //敵死亡カウントUP
	 
	int GetCannonCount() { return cannonCount; }         //砲台の生きている数
private:
	//Wave
	void WaveUpdate(float deltaTime);

	//ウェイブ管理
	void Wave_1(float deltaTime);
	void Wave_2(float deltaTime);
	void Wave_3(float deltaTime);
	void ChangeWave(StageWave wave);

private:
	
	StageWave nowSatge;
	int enemyDeadCount;                  //敵死亡カウント
	int cannonCount;                     //生成されている砲台をカウント
	int cannonGenerateCount;             //大砲生成カウント
	GameObjectManager m_pGameManager;    //ゲームオブジェクトマネージャー
};