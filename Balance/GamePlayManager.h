#pragma once

//	�Q�[���v���C�Ǘ��N���X
class GamePlayManager
{
private:
	GamePlayManager(){}
	GamePlayManager(const GamePlayManager&) {}
	GamePlayManager& operator=(const GamePlayManager&) {}
public:

	//	�C���X�^���X���擾
	static GamePlayManager& Instance();

	//	���[�v����
	void Update();

	//  �X�V����
	void GameUpdate();
};