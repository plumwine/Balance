#include <DxLib.h>
#include <memory>
#include "GamePlayManager.h"
#include "FPS.h"


//	�N���X�̃C���X�^���X���擾
GamePlayManager & GamePlayManager::Instance()
{
	static std::unique_ptr<GamePlayManager> instance(new GamePlayManager);

	return *instance;
}

void GamePlayManager::Initialize()
{
	m_pCannon = new Cannon(Vector2(100, 100), Vector2(32, 32), 1, 1);
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
		GameUpdate();

		//	�X�V
		fps.Update();
		fps.Draw();

		ScreenFlip();

		fps.Wait();
	}
}

//	�X�V����
void GamePlayManager::GameUpdate()
{

	m_pCannon->Draw();
}