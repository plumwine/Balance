#include <DxLib.h>
#include <memory>
#include "GamePlayManager.h"
#include "FPS.h"
#include "GraphFactory.h"


//	�N���X�̃C���X�^���X���擾
GamePlayManager & GamePlayManager::Instance()
{
	static std::unique_ptr<GamePlayManager> instance(new GamePlayManager);

	return *instance;
}

void GamePlayManager::Initialize()
{
	m_pGameManager = new GameObjectManager();
	m_pGameManager->Add(new Cannon(Vector2(100, 100), Vector2(32, 32), 0));
	m_pGameManager->Add(new Bullet(Vector2(100, 100), Vector2(32, 32), Vector2(1,1)));
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
	m_pGameManager->Update(deltaTime);

	m_pGameManager->Draw();

}