#pragma once
#include "Cannon.h"
#include "Bullet.h"

#include "Render.h"
#include "GameObjectManager.h"

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


private:
	Cannon* m_pCannon;
	GameObjectManager* m_pGameManager;
};