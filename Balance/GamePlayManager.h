#pragma once

//	ゲームプレイ管理クラス
class GamePlayManager
{
private:
	GamePlayManager(){}
	GamePlayManager(const GamePlayManager&) {}
	GamePlayManager& operator=(const GamePlayManager&) {}
public:

	//	インスタンスを取得
	static GamePlayManager& Instance();

	//	ループ処理
	void Update();

	//  更新処理
	void GameUpdate();
};