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


	m_pGameManager.Add(new Player(Vector2(100, 500), p_pGameManager));
	m_pGameManager.Add(new Cannon(Vector2(300, 0), p_pGameManager, 0));
	m_pGameManager.Add(new Bullet(Vector2(100, 100), Vector2(1,1)));
	m_pGameManager.Add(new Enemy(Vector2(800, 500), Vector2(-1,0)));
	m_pGameManager.Add(new Ground(Vector2(0, 550)));
	
}

//	ループ処理
void GamePlayManager::Update(float deltaTime)
{
	Fps fps;
	//	メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//	背景をクリアする
		ClearDrawScreen();

		//	シーンを更新する
		GameUpdate(deltaTime);

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
	m_pGameManager.Update(deltaTime);
	m_pGameManager.Draw();

}