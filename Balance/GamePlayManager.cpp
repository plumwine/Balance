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
	m_pGameManager = new GameObjectManager();

	m_EnemyManager =  EnemyGenerateManager();
	m_EnemyManager.Initialize(m_pGameManager);

	input = Input();

	endGr = LoadGraph("../Texture/kari/sipai_A.png");
	golGr = LoadGraph("../Texture/kari/seikou_A.png");
	gameEnd = false;

	//最初に生成するものを各Wave共通
	m_pGameManager->Add(new Player(Vector2(900, 832)));

	cannonCount++;
	m_pGameManager->Add(new Cannon(Vector2(960, 000), m_pGameManager,cannonCount));
	cannonCount++;
	m_pGameManager->Add(new Cannon(Vector2(960, 100), m_pGameManager,cannonCount));
	cannonCount++;
	m_pGameManager->Add(new Cannon(Vector2(960, 200), m_pGameManager,cannonCount));
	cannonCount++;
	m_pGameManager->Add(new Cannon(Vector2(960, 300), m_pGameManager,cannonCount));
	cannonCount++;
	m_pGameManager->Add(new Cannon(Vector2(960, 400), m_pGameManager,cannonCount));

	m_pGameManager->Add(new Ground(Vector2(0, 870)));
	
	//最初はSatge1
	nowSatge = StageWave::Stage1;
	nowScene = Scene::GamePlayScene;
	

}

//	ループ処理
void GamePlayManager::Update()
{
	Fps fps;
	fps.TimeStart();

	//	メインループ
	while (ProcessMessage() == 0 && !(CheckHitKey(KEY_INPUT_ESCAPE) == 1 || input.GetButtonState(INPUT_BUTTON_BACK, DX_INPUT_PAD1)))
	{
		//	背景をクリアする
		ClearDrawScreen();

		//	シーンを更新する
		SceneUpdate(fps.DeltaTime());
		//	更新
		fps.Update();
		fps.Draw();
		//変更点
		m_EnemyManager.Update(fps.GetTime(), cannonCount);
		

		ScreenFlip();

		fps.Wait();
	}
}

//	更新処理
void GamePlayManager::GameUpdate(float deltaTime)
{
	m_pGameManager->Update(deltaTime);
	m_pGameManager->Draw();

	WaveUpdate(deltaTime);
	CountMnager();
	

}

void GamePlayManager::SceneUpdate(float deltaTime)
{
	switch (nowScene)
	{
	case TitleScene:
		Title();
		break;
	case GamePlayScene:
		GameUpdate(deltaTime);
		break;
	case EndScene:
		Ending();
		break;
	case InitScene:
		Init();
		break;
	}

}

void GamePlayManager::Title()
{

}
void GamePlayManager::Ending()
{
}

void GamePlayManager::CangeScene(Scene scene)
{
	nowScene = scene;
}

void GamePlayManager::Init()
{
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
		cannonGenerateCount = 5;
	//出せる大砲が１個以上あると生成できる
	if (cannonGenerateCount >= 1)
	{
		//Aボタンを押したらCannonを生成
		if (input.GetButtonTrigger(INPUT_BUTTON_A, DX_INPUT_PAD1))
		{
			cannonGenerateCount--;
			cannonCount++;
			m_pGameManager->Add(new Cannon(Vector2(960, 200), m_pGameManager, cannonCount));
		}

	}

	//箱が床に落ちたら終了
	if (gameEnd)
	{
		DrawTurnGraph(600, 200, endGr,1);
	}
	if (cannonCount>=10)
	{
		DrawTurnGraph(600, 200, golGr, 0);
	}


}
