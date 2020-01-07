#include <DxLib.h>
#include <memory>
#include "FPS.h"
#include "GraphFactory.h"
#include "Render.h"
//オブジェクト関係
#include "GamePlayManager.h"
#include "Player.h"
#include "Cannon.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Ground.h"

//	クラスのインスタンスを取得
GamePlayManager & GamePlayManager::Instance()
{
	static std::unique_ptr<GamePlayManager> instance(new GamePlayManager);

	return *instance;
}

void GamePlayManager::Initialize()
{
	 
	GameObjectManager* p_pGameManager;
	p_pGameManager = &m_pGameManager;
	p_pGameManager = new GameObjectManager();

	//最初に生成するものを各Wave共通
	m_pGameManager.Add(new Player(Vector2(100, 832)));
	cannonCount++;
	m_pGameManager.Add(new Cannon(Vector2(300, 000), p_pGameManager,cannonCount));
	cannonCount++;
	m_pGameManager.Add(new Cannon(Vector2(300, 100), p_pGameManager,cannonCount));
	cannonCount++;
	m_pGameManager.Add(new Cannon(Vector2(300, 200), p_pGameManager,cannonCount));
	cannonCount++;
	m_pGameManager.Add(new Cannon(Vector2(300, 300), p_pGameManager,cannonCount));
	cannonCount++;
	m_pGameManager.Add(new Cannon(Vector2(300, 400), p_pGameManager,cannonCount));
	cannonCount++;
	m_pGameManager.Add(new Ground(Vector2(0, 870)));
	
	//最初はSatge1
	nowSatge = StageWave::Stage1;

}

//	ループ処理
void GamePlayManager::Update()
{
	Fps fps;
	//	メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//	背景をクリアする
		ClearDrawScreen();

		//	シーンを更新する
		GameUpdate(fps.DeltaTime());

		//	更新
		fps.Update();
		fps.Draw();

		ScreenFlip();

		fps.Wait();
	}
}

//	更新処理
void GamePlayManager::GameUpdate(float deltaTime)
{

	WaveUpdate(deltaTime);

	m_pGameManager.Update(deltaTime);
	m_pGameManager.Draw();

}

//ウェイブ管理
void GamePlayManager::WaveUpdate(float deltaTime)
{
	switch (nowSatge)
	{
		case Stage1:
			Wave_1(deltaTime);
			break;
		case Stage2:
			Wave_2(deltaTime);
			break;
		case Stage3:
			Wave_3(deltaTime);
			break;
	}
}

void GamePlayManager::Wave_1(float deltaTime)
{
}

void GamePlayManager::Wave_2(float deltaTime)
{
}

void GamePlayManager::Wave_3(float deltaTime)
{
}
//WAVEチェンジ
void GamePlayManager::ChangeWave(StageWave wave)
{
	nowSatge = wave;
}

//カウントの管理
void GamePlayManager::CountMnager()
{
	//エネミーを一定数倒したら、一回大砲を生成できるカウントを＋
	if (enemyDeadCount >= 3)
	{
		enemyDeadCount = 0;
		cannonGenerateCount++;
	}
	//ため込める大砲の数を取得
	if (cannonGenerateCount >= 5)
		cannonCount = 5;
}
