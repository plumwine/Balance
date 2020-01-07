#pragma once
#include "GameObjectManager.h"
#include <vector>



enum StageWave
{
	Stage1,
	Stage2,
	Stage3
};

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
	void GameUpdate(float deltaTime);
	void EnemyDeadCountUp() { enemyDeadCount++; };       //�G���S�J�E���gUP
	 
	int GetCannonCount() { return cannonCount; }         //�C��̐����Ă��鐔
private:
	//Wave
	void WaveUpdate(float deltaTime);

	//�E�F�C�u�Ǘ�
	void Wave_1(float deltaTime);
	void Wave_2(float deltaTime);
	void Wave_3(float deltaTime);
	void ChangeWave(StageWave wave);

private:
	
	StageWave nowSatge;
	int enemyDeadCount;                  //�G���S�J�E���g
	int cannonCount;                     //��������Ă���C����J�E���g
	int cannonGenerateCount;             //��C�����J�E���g
	GameObjectManager m_pGameManager;    //�Q�[���I�u�W�F�N�g�}�l�[�W���[
};