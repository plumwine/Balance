#pragma once
#include "Cannon.h"
#include "Bullet.h"

#include "Render.h"
#include "GameObjectManager.h"

//	�Q�[���v���C�Ǘ��N���X
class GamePlayManager
{
private:
	GamePlayManager() { Initialize(); }
	GamePlayManager(const GamePlayManager&) { Initialize(); }
	GamePlayManager& operator=(const GamePlayManager&) {}
public:

	//	�C���X�^���X���擾
	static GamePlayManager& Instance();

	void Initialize(); //������

	//	���[�v����
	void Update(float deltaTime);

	//  �X�V����
	void GameUpdate(float deltaTime);


private:
	Cannon* m_pCannon;
	GameObjectManager* m_pGameManager;
};