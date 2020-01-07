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
	 
	GameObjectManager* p_pGameManager;
	p_pGameManager = &m_pGameManager;
	p_pGameManager = new GameObjectManager();

	//�ŏ��ɐ���������̂��eWave����
	m_pGameManager.Add(new Player(Vector2(100, 832)));
	cannonCount++;
	m_pGameManager.Add(new Cannon(Vector2(300, 000), p_pGameManager,cannonCount));
	cannonCount++;
	m_pGameManager.Add(new Cannon(Vector2(300, 100), p_pGameManager,cannonCount));
	cannonCount++;
	m_pGameManager.Add(new Cannon(Vector2(300, 200), p_pGameManager,cannonCount));
	cannonCount++;
	m_pGameManager.Add(new Cannon(Vector2(300, 300), p_pGameManager,cannonCount));
	cannonCount++;
	m_pGameManager.Add(new Cannon(Vector2(300, 400), p_pGameManager,cannonCount));
	cannonCount++;
	m_pGameManager.Add(new Ground(Vector2(0, 870)));
	
	//�ŏ���Satge1
	nowSatge = StageWave::Stage1;

}

//	���[�v����
void GamePlayManager::Update()
{
	Fps fps;
	//	���C�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//	�w�i���N���A����
		ClearDrawScreen();

		//	�V�[�����X�V����
		GameUpdate(fps.DeltaTime());

		//	�X�V
		fps.Update();
		fps.Draw();

		ScreenFlip();

		fps.Wait();
	}
}

//	�X�V����
void GamePlayManager::GameUpdate(float deltaTime)
{

	WaveUpdate(deltaTime);

	m_pGameManager.Update(deltaTime);
	m_pGameManager.Draw();

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
		cannonCount = 5;
}
