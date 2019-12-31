#pragma once
#include "Cannon.h"
#include "Bullet.h"


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
	void Update();

	//  �X�V����
	void GameUpdate();


private:
	Cannon* m_pCannon;

};