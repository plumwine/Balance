#pragma once
#include "GameObjectManager.h"
#include "Input.h"
#include "EnemyGenerateManager.h"
#include "FPS.h"

//ゲーム循環enum
enum Scene
{
	TitleScene,
	GamePlayScene,
	EndScene,
};


//ゲームプレイ用
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
	~GamePlayManager();

	void Initialize(); //初期化

	//	ループ処理
	void Update();
	//仮
	void endGame() { gameEnd = true; }

	//  更新処理
	void GameUpdate(float deltaTime);
	void EnemyDeadCountUp() { enemyDeadCount++; };       //敵死亡カウントUP
	void DeadCannon() { cannonCount--; }
	int GetCannonCount() { return cannonCount; }         //砲台の生きている数

private:
	//シーン管理
	void SceneUpdate(float deltaTime);
	void Title();
	void Ending();
	void ChangeScene(Scene scene);
	void Init();

	//Wave
	void WaveUpdate(float deltaTime);

	//ウェイブ管理
	void Wave_1(float deltaTime);
	void Wave_2(float deltaTime);
	void Wave_3(float deltaTime);
	void ChangeWave(StageWave wave);
	void CountMnager();

private:
	
	int endGr;
	int golGr;
	Scene nowScene;                      //現在のシーン
	bool gameEnd;                        //ゲームエンド（仮）
	Input input; 
	StageWave nowSatge;
	int enemyDeadCount;                  //敵死亡カウント
	int cannonCount;                     //生成されている砲台をカウント
	int cannonGenerateCount;             //大砲生成カウント

	EnemyGenerateManager m_EnemyManager; //敵生成クラス
	GameObjectManager* m_pGameManager;   //ゲームオブジェクトマネージャー

	Fps fps;                             //ゲーム時間管理

};