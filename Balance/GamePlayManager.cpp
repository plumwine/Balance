#include <DxLib.h>
#include <memory>
#include "GraphFactory.h"
#include "Render.h"
#include "Music.h"
//オブジェクト関係
#include "GamePlayManager.h"
#include "Player.h"
#include "Cannon.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Ground.h"
#include "WaveLine.h"

//	クラスのインスタンスを取得
GamePlayManager & GamePlayManager::Instance()
{
	static std::unique_ptr<GamePlayManager> instance(new GamePlayManager);

	return *instance;
}

GamePlayManager::~GamePlayManager()
{
	delete m_pGameManager;
}

void GamePlayManager::Initialize()
{
	
	nowScene = Scene::LoadScene;
	//最初はSatge1
	nowSatge = StageWave::Stage1;
	playerPos = Vector2(960, 808);
	gameEnd = false;
	cannonCount = 0;
	waveline_Y = 600;
	topCannon_Y = 808;   //頂点のYを取得
}

//	ループ処理
void GamePlayManager::Update()
{

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
	Ending();
	//描画順んは後が高くなる
	//背景描画
	topCannon_Y = m_pGameManager->TopCannon();
	m_pGameManager->Update(deltaTime);
	m_pGameManager->Draw();

	Render::Instance().RectParticle(Vector2(10, 900), enemyDeadCount * 3, 192, gage_Gr, false);   //ゲージ
	Render::Instance().NumberDraw_Small(Vector2(40, 940), cannonGenerateCount, subNumGr);          //大砲生成可能数
	Render::Instance().NumberDraw(Vector2(100, 100), fps.GetTime(), numberGr);

	Render::Instance().NumberDraw(Vector2(1800, 1000), score, numberGr);
	DrawGraph(1000, 1000, score_Text, 0); //スコアテキスト
	
	CountMnager();
}

void GamePlayManager::SceneUpdate(float deltaTime)
{
	switch (nowScene)
	{
	case TitleScene:
		Title(deltaTime);
		break;
	case GamePlayScene:
		WaveUpdate(deltaTime);
		if (!Music::Instance().CheckSound(stageBGM))
		{
			Music::Instance().SoundFileStart(stageBGM, DX_PLAYTYPE_LOOP);
		}
		break;
	case LoadScene:
		Load();
		break;
	}

}
void GamePlayManager::Load()
{
	m_pGameManager = new GameObjectManager();
	m_EnemyManager = EnemyGenerateManager();
	m_EnemyManager.Initialize(m_pGameManager);
	fps = Fps();
	input = Input();

	//絵の登録
	title_Gr = GraphFactory::Instance().LoadGraph("../Texture/master/Shake.png");      //タイトル
	gage_Gr = GraphFactory::Instance().LoadGraph("../Texture/master/zouka.png");       //ゲージ
	endGr = GraphFactory::Instance().LoadGraph("../Texture/kari/sipai_A.png");
	golGr = GraphFactory::Instance().LoadGraph("../Texture/kari/seikou_A.png");
	back_Gr_1 = GraphFactory::Instance().LoadGraph("../Texture/master/Haikei.png");    //朝
	back_Gr_2 = GraphFactory::Instance().LoadGraph("../Texture/master/sunset.png");    //昼
	back_Gr_3 = GraphFactory::Instance().LoadGraph("../Texture/master/night.png");     //夜
	result = GraphFactory::Instance().LoadGraph("../Texture/master/result.png");
	numberGr = GraphFactory::Instance().LoadGraph("../Texture/master/Renban.png");
	subNumGr = GraphFactory::Instance().LoadGraph("../Texture/master/subNum.png");
	//テキスト
	gameplay_Text = GraphFactory::Instance().LoadGraph("../Texture/master/GamePlay.png");
	pushstart_Text = GraphFactory::Instance().LoadGraph("../Texture/master/PushStart.png");
	title_Text = GraphFactory::Instance().LoadGraph("../Texture/master/title.png");
	score_Text = GraphFactory::Instance().LoadGraph("../Texture/master/score.png");
	//音
	//SE
	boyon1 = Music::Instance().LoadSound("../Music/boyon1.wav");
	hyun1 = Music::Instance().LoadSound("../Music/hyun1.wav");
	button = Music::Instance().LoadSound("../Music/button.wav");
	//BGM
	stageBGM = Music::Instance().LoadSound("../Music/stageBGM.wav");
	titleBGM = Music::Instance().LoadSound("../Music/title.ogg");
	resultBGM = Music::Instance().LoadSound("../Music/MusMusResult.ogg");


	DrawExtendGraph(0, 0, 1980, 1080, back_Gr_1, false);
	Initialize();
	//キャノンを追加するときはcannnonCountを足す
	cannonCount = 1;
	cannonGenerateCount = 0;
	enemyDeadCount = 0;
	//最初に生成するものを各Wave共通

	m_pGameManager->Add(new Ground(Vector2(0, 936)));
	m_pGameManager->Add(new Player(Vector2(960, 808)));  //Player
	m_pGameManager->Add(new Cannon(Vector2(960, 600), m_pGameManager, cannonCount)); //Canon

	//全て終わったらタイトルに行く
	ChangeScene(Scene::TitleScene);

}
//タイトル
void GamePlayManager::Title(float deltaTime)
{
	fps.Wait();
	fps.TimeStop();
	if (!Music::Instance().CheckSound(titleBGM))
	{
		Music::Instance().SoundFileStart(titleBGM, DX_PLAYTYPE_LOOP);
	}
	DrawExtendGraph(0, 0, 1980, 1080, back_Gr_1, false);
	Render::Instance().Draw(Vector2(400, 20), Vector2(1020, 560), title_Gr);
	if (input.GetButtonTrigger(INPUT_BUTTON_START, DX_INPUT_PAD1))
	{
		Music::Instance().SoundStop(titleBGM);
		Music::Instance().SoundFileStart(button, DX_PLAYTYPE_NORMAL);
		Initialize();
		Init();
		fps.TimeStart();
		score = 0;//スコアを初期値に設定
		ChangeScene(Scene::GamePlayScene);
	}
	m_pGameManager->Update(deltaTime);
	m_pGameManager->Draw();

	

}
//エンディング
void GamePlayManager::Ending()
{
	if (!gameEnd) return;
	DrawTurnGraph(300, 200, result, 0);
	Render::Instance().NumberDraw(Vector2(700, 500), score, numberGr);
	
	if (input.GetButtonTrigger(INPUT_BUTTON_START, DX_INPUT_PAD1))
	{
		Initialize();
		Init();
		fps.TimeStart();
		score = 0;//スコアを初期値に設定
		ChangeScene(Scene::LoadScene);
		if (Music::Instance().CheckSound(stageBGM))
		{
			Music::Instance().SoundStop(stageBGM);
		}
		if (!Music::Instance().CheckSound(resultBGM))
		{
			Music::Instance().SoundFileStart(resultBGM,DX_PLAYTYPE_LOOP);
		}
		if (input.GetButtonTrigger(INPUT_BUTTON_START, DX_INPUT_PAD1))
		{
			if (Music::Instance().CheckSound(resultBGM))
			{
				Music::Instance().SoundStop(resultBGM);
			}
			ChangeScene(Scene::TitleScene);
		}
	}
}

void GamePlayManager::ChangeScene(Scene scene)
{
	nowScene = scene;
}

void GamePlayManager::Init()
{
	m_pGameManager->Clear();
	m_EnemyManager.Initialize(m_pGameManager);

	gameEnd = false;
	//キャノンを追加するときはcannnonCountを足す
	cannonCount = 1;
	cannonGenerateCount = 0;
	enemyDeadCount = 0;
	//最初に生成するものを各Wave共通

	m_pGameManager->Add(new Ground(Vector2(0, 936)));
	m_pGameManager->Add(new Player(Vector2(960, 808)));  //Player
	m_pGameManager->Add(new Cannon(Vector2(960, 600), m_pGameManager, cannonCount)); //Canon
	m_pGameManager->Add(new WaveLine(Vector2(0, 500)));
}

//ウェイブ管理
void GamePlayManager::WaveUpdate(float deltaTime)
{
	switch (nowSatge)
	{
	case Stage1:
		DrawExtendGraph(0, 0, 1980, 1080, back_Gr_1, false);
		Wave_1(deltaTime);
		break;
	case Stage2:
		DrawExtendGraph(0, 0, 1980, 1080, back_Gr_2, false);
		Wave_2(deltaTime);
		break;
	case Stage3:
		DrawExtendGraph(0, 0, 1980, 1080, back_Gr_3, false);
		Wave_3(deltaTime);
		break;
	}
}

void GamePlayManager::Wave_1(float deltaTime)
{
	GameUpdate(deltaTime);
	if (topCannon_Y <= waveline_Y)
	{
		fps.Wait();
		ChangeWave(StageWave::Stage2);
		Init();
		fps.TimeStart();
	}
}

void GamePlayManager::Wave_2(float deltaTime)
{
	GameUpdate(deltaTime);
	if (topCannon_Y <= waveline_Y)
	{
		fps.Wait();
		ChangeWave(StageWave::Stage3);
		Init();
		fps.TimeStart();
	}
}

void GamePlayManager::Wave_3(float deltaTime)
{
	GameUpdate(deltaTime);
	if (topCannon_Y <= waveline_Y)
	{
		gameEnd = true;
		fps.Wait();
	}
}
StageWave GamePlayManager::GetWave()
{
	return nowSatge;
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
	//ため込める大砲の数制限
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
			m_pGameManager->Add(new Cannon(Vector2(playerPos.x, -100), m_pGameManager, cannonCount));
		}
	}
	if (cannonCount <= 0)
	{
		gameEnd = true;
	}
}

//得点を足す
void GamePlayManager::ScoreUp()
{
	score += 10;
}

void GamePlayManager::GetPlayerPos(Vector2 pos)
{
	playerPos = pos;
}
