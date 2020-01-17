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
	nowScene = Scene::TitleScene;
	//�ŏ���Satge1
	nowSatge = StageWave::Stage1;
	endGr = GraphFactory::Instance().LoadGraph("../Texture/kari/sipai_A.png");
	golGr = GraphFactory::Instance().LoadGraph("../Texture/kari/seikou_A.png");
	back_Gr = GraphFactory::Instance().LoadGraph("../Texture/master/Haikei.png");
	numberGr = GraphFactory::Instance().LoadGraph("../Texture/master/Renban.png");

	//int a = Music::Instance().LoadSound("boyon1", Type::wav);

	gameEnd = false;
	cannonCount = 0;
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
		m_EnemyManager.Update(fps.GetTime(), cannonCount);
		

		ScreenFlip();

		fps.Wait();
	}
}

//	�X�V����
void GamePlayManager::GameUpdate(float deltaTime)
{
	//�`�揇��͌オ�����Ȃ�
	//�w�i�`��
	DrawExtendGraph(0, 0, 1980, 1080, back_Gr, false);
	m_pGameManager->Update(deltaTime);
	m_pGameManager->Draw();

	//Render::Instance().NumberDraw(Vector2(100, 100), fps.GetTime(), numberGr);

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
		WaveUpdate(deltaTime);
		
		break;
	case EndScene:
		Ending();
		break;
	}

}
//�^�C�g��
void GamePlayManager::Title()
{
	
	if (input.GetButtonTrigger(INPUT_BUTTON_START, DX_INPUT_PAD1))
	{
		Initialize();
		Init();
		fps.TimeStart();
		ChangeScene(Scene::GamePlayScene);
	}

}
//�G���f�B���O
void GamePlayManager::Ending()
{
	if (input.GetButtonTrigger(INPUT_BUTTON_START, DX_INPUT_PAD1))
	{
		ChangeScene(Scene::TitleScene);
	}
	if (gameEnd || (cannonCount <= 0))
	{
		DrawTurnGraph(600, 200, endGr, 1);
	}
	if (cannonCount >= 10)
	{
		DrawTurnGraph(600, 200, golGr, 0);
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

	m_pGameManager->Add(new Ground(Vector2(0, 870)));
	m_pGameManager->Add(new Player(Vector2(960, 832)));
	m_pGameManager->Add(new Cannon(Vector2(960, 800), m_pGameManager, cannonCount));

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
	if (cannonCount >= 10)
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
	if (cannonCount >= 10)
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
	if (cannonCount >= 10)
	{
		fps.Wait();
		ChangeScene(Scene::EndScene);
		Init();
		DrawTurnGraph(600, 200, golGr, 0);
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
	//���ߍ��߂��C�̐����擾
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
			m_pGameManager->Add(new Cannon(Vector2(m_pGameManager->TopCannon(), 200), m_pGameManager, cannonCount));
		}
	}
	//�������ɗ�������I��
	if (gameEnd || (cannonCount <=0))
	{
		fps.Wait();
		ChangeScene(Scene::EndScene);
		DrawTurnGraph(600, 200, endGr,1);
	}
}
