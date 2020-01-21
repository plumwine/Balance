#include <DxLib.h>
#include <memory>
#include "GraphFactory.h"
#include "Render.h"
#include "Music.h"
//�I�u�W�F�N�g�֌W
#include "GamePlayManager.h"
#include "Player.h"
#include "Cannon.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Ground.h"
#include "WaveLine.h"

//	�N���X�̃C���X�^���X���擾
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
	m_pGameManager = new GameObjectManager();
	m_EnemyManager =  EnemyGenerateManager();
	m_EnemyManager.Initialize(m_pGameManager);
	fps =  Fps();
	input = Input();
	nowScene = Scene::LoadScene;
	//�ŏ���Satge1
	nowSatge = StageWave::Stage1;
	title_Gr = GraphFactory::Instance().LoadGraph("../Texture/master/Shake.png");      //�^�C�g��
	gage_Gr = GraphFactory::Instance().LoadGraph("../Texture/master/zouka.png");       //�Q�[�W
	endGr = GraphFactory::Instance().LoadGraph("../Texture/kari/sipai_A.png");
	golGr = GraphFactory::Instance().LoadGraph("../Texture/kari/seikou_A.png");
	back_Gr = GraphFactory::Instance().LoadGraph("../Texture/master/Haikei.png");
	result = GraphFactory::Instance().LoadGraph("../Texture/master/result.png");
	numberGr = GraphFactory::Instance().LoadGraph("../Texture/master/Renban.png");
	subNumGr = GraphFactory::Instance().LoadGraph("../Texture/master/subNum.png");

	boyon1 = Music::Instance().LoadSound("../Music/boyon1.wav");
	hyun1 = Music::Instance().LoadSound("../Music/hyun1.wav");
	button = Music::Instance().LoadSound("../Music/button.wav");

	stageBGM = Music::Instance().LoadSound("../Music/stageBGM.wav");

	playerPos = Vector2(960, 808);
	gameEnd = false;
	cannonCount = 0;
	waveline_Y = 100;
}

//	���[�v����
void GamePlayManager::Update()
{
	
	fps.TimeStart();

	//	���C�����[�v
	while (ProcessMessage() == 0 && !(CheckHitKey(KEY_INPUT_ESCAPE) == 1 || input.GetButtonState(INPUT_BUTTON_BACK, DX_INPUT_PAD1)))
	{
		//	�w�i���N���A����
		ClearDrawScreen();

		//	�V�[�����X�V����
		SceneUpdate(fps.DeltaTime());
		//	�X�V
		fps.Update();
		fps.Draw();
		//�ύX�_
		m_EnemyManager.Update(fps.GetTime(),cannonCount);
		

		ScreenFlip();

		fps.Wait();
	}
}

//	�X�V����
void GamePlayManager::GameUpdate(float deltaTime)
{
	Ending();
	//�`�揇��͌オ�����Ȃ�
	//�w�i�`��
	DrawExtendGraph(0, 0, 1980, 1080, back_Gr, false);
	m_pGameManager->Update(deltaTime);
	m_pGameManager->Draw();
	if (gameEnd) return;
	
	

	Render::Instance().RectParticle(Vector2(10, 900), enemyDeadCount * 3, 192, gage_Gr, false);   //�Q�[�W
	Render::Instance().NumberDraw_Small(Vector2(40, 940), cannonGenerateCount, subNumGr);          //��C�����\��
	
	Render::Instance().NumberDraw(Vector2(100, 100), fps.GetTime(), numberGr);
	Render::Instance().NumberDraw(Vector2(1700, 950), score, numberGr);
	topCannon_Y = 808;   //���_��Y���擾

	
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
	DrawExtendGraph(0, 0, 1980, 1080, back_Gr, false);
	Initialize();
	//�L���m����ǉ�����Ƃ���cannnonCount�𑫂�
	cannonCount = 1;
	cannonGenerateCount = 0;
	enemyDeadCount = 0;
	//�ŏ��ɐ���������̂��eWave����

	m_pGameManager->Add(new Ground(Vector2(0, 936)));
	m_pGameManager->Add(new Player(Vector2(960, 808)));  //Player
	m_pGameManager->Add(new Cannon(Vector2(960, 600), m_pGameManager, cannonCount)); //Canon
	
	ChangeScene(Scene::TitleScene);

}
//�^�C�g��
void GamePlayManager::Title(float deltaTime)
{
	fps.Wait();
	fps.TimeStop();
	DrawExtendGraph(0, 0, 1980, 1080, back_Gr, false);
	Render::Instance().Draw(Vector2(400, 20), Vector2(1020, 560), title_Gr);
	if (input.GetButtonTrigger(INPUT_BUTTON_START, DX_INPUT_PAD1))
	{
		Music::Instance().SoundFileStart(button,DX_PLAYTYPE_NORMAL);
		Initialize();
		Init();
		fps.TimeStart();
		score = 0;//�X�R�A�������l�ɐݒ�
		ChangeScene(Scene::GamePlayScene);
	}
	m_pGameManager->Update(deltaTime);
	m_pGameManager->Draw();

	

}
//�G���f�B���O
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
		score = 0;//�X�R�A�������l�ɐݒ�
		ChangeScene(Scene::LoadScene);
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
	//�L���m����ǉ�����Ƃ���cannnonCount�𑫂�
	cannonCount = 1;
	cannonGenerateCount = 0;
	enemyDeadCount = 0;
	//�ŏ��ɐ���������̂��eWave����

	m_pGameManager->Add(new Ground(Vector2(0, 936)));
	m_pGameManager->Add(new Player(Vector2(960, 808)));  //Player
	m_pGameManager->Add(new Cannon(Vector2(960, 600), m_pGameManager,cannonCount)); //Canon
	m_pGameManager->Add(new WaveLine(Vector2(0, 100)));
}

//�E�F�C�u�Ǘ�
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
//WAVE�`�F���W
void GamePlayManager::ChangeWave(StageWave wave)
{
	nowSatge = wave;
}

//�J�E���g�̊Ǘ�
void GamePlayManager::CountMnager()
{
	//�G�l�~�[����萔�|������A����C�𐶐��ł���J�E���g���{
	if (enemyDeadCount >= 3)
	{
		enemyDeadCount = 0;
		cannonGenerateCount++;
	}
	//���ߍ��߂��C�̐�����
	if (cannonGenerateCount >= 5)
		cannonGenerateCount = 5;
	//�o�����C���P�ȏ゠��Ɛ����ł���
	if (cannonGenerateCount >= 1)
	{
		//A�{�^������������Cannon�𐶐�
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

//���_�𑫂�
void GamePlayManager::ScoreUp()
{
	score += 10;
}

void GamePlayManager::GetPlayerPos(Vector2 pos)
{
	playerPos = pos;
}
