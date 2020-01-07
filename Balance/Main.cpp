#include <DxLib.h>
#include <string>
#include "WindowInfo.h"
#include "GamePlayManager.h"


//金井編集リポジトリ確認用
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//	Windowモードの設定とWindowタイトルを設定する
	ChangeWindowMode(true);
	SetMainWindowText("Balance");

	//	画面サイズを設定
	SetGraphMode(WindowInfo::WindowWidth, WindowInfo::WindowHeight, 16);
	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;				// エラーが起きたら直ちに終了
	}

	//	描画先を指定
	SetDrawScreen(DX_SCREEN_BACK);

	//	画面背景の色を設定する
	SetBackgroundColor(0, 0, 0);
	//	実行
	GamePlayManager::Instance().Update();

	//	解放処理
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}