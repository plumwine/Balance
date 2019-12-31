#include <DxLib.h>
#include <memory>
#include "GamePlayManager.h"
#include "FPS.h"


//	クラスのインスタンスを取得
GamePlayManager & GamePlayManager::Instance()
{
	static std::unique_ptr<GamePlayManager> instance(new GamePlayManager);

	return *instance;
}

void GamePlayManager::Initialize()
{
	m_pCannon = new Cannon(Vector2(100, 100), Vector2(32, 32), 1, 1);
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
		GameUpdate();

		//	更新
		fps.Update();
		fps.Draw();

		ScreenFlip();

		fps.Wait();
	}
}

//	更新処理
void GamePlayManager::GameUpdate()
{

	m_pCannon->Draw();
}