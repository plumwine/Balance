#include <DxLib.h>
#include <memory>
#include "FPS.h"
#include "GraphFactory.h"
#include "Render.h"
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

void GamePlayManager::Initialize()
{
	m_pGameManager = new GameObjectManager();

	m_EnemyManager =  EnemyGenerateManager();
	m_EnemyManager.Initialize(m_pGameManager);

	input = Input();

	endGr = LoadGraph("../Texture/kari/sipai_A.png");
	golGr = LoadGraph("../Texture/kari/seikou_A.png");
	gameEnd = false;

	//�ŏ��ɐ���������̂��eWave����
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
	
	//�ŏ���Satge1
	nowSatge = StageWave::Stage1;
	nowScene = Scene::GamePlayScene;
	

}

//	���[�v����
void GamePlayManager::Update()
{
	Fps fps;
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
}

void GamePlayManager::Wave_2(float deltaTime)
{
}

void GamePlayManager::Wave_3(float deltaTime)
{
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
			m_pGameManager->Add(new Cannon(Vector2(960, 200), m_pGameManager, cannonCount));
		}

	}

	//�������ɗ�������I��
	if (gameEnd)
	{
		DrawTurnGraph(600, 200, endGr,1);
	}
	if (cannonCount>=10)
	{
		DrawTurnGraph(600, 200, golGr, 0);
	}


}
