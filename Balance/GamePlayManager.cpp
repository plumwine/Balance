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
	m_pGameManager.Add(new Player(Vector2(100, 500), p_pGameManager));
	m_pGameManager.Add(new Cannon(Vector2(300, 0), p_pGameManager, 0));
	m_pGameManager.Add(new Bullet(Vector2(100, 100), Vector2(1,1)));
	m_pGameManager.Add(new Enemy(Vector2(800, 500), Vector2(-1,0)));
	m_pGameManager.Add(new Ground(Vector2(0, 550)));
	
	//�ŏ���Satge1
	nowSatge = StageWave::Stage1;

}

//	���[�v����
void GamePlayManager::Update(float deltaTime)
{
	Fps fps;
	//	���C�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//	�w�i���N���A����
		ClearDrawScreen();

		//	�V�[�����X�V����
		GameUpdate(deltaTime);

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

void GamePlayManager::ChangeWave(StageWave wave)
{
}
