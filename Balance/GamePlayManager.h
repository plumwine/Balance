#pragma once
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
	GameObjectManager m_pGameManager;
};