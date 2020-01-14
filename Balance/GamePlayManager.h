#pragma once
#include "GameObjectManager.h"
#include "Input.h"
#include "EnemyGenerateManager.h"
#include "FPS.h"

//�Q�[���z��enum
enum Scene
{
	TitleScene,
	GamePlayScene,
	EndScene,
};


//�Q�[���v���C�p
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
	~GamePlayManager();

	void Initialize(); //������

	//	���[�v����
	void Update();
	//��
	void endGame() { gameEnd = true; }

	//  �X�V����
	void GameUpdate(float deltaTime);
	void EnemyDeadCountUp() { enemyDeadCount++; };       //�G���S�J�E���gUP
	void DeadCannon() { cannonCount--; }
	int GetCannonCount() { return cannonCount; }         //�C��̐����Ă��鐔

private:
	//�V�[���Ǘ�
	void SceneUpdate(float deltaTime);
	void Title();
	void Ending();
	void ChangeScene(Scene scene);
	void Init();

	//Wave
	void WaveUpdate(float deltaTime);

	//�E�F�C�u�Ǘ�
	void Wave_1(float deltaTime);
	void Wave_2(float deltaTime);
	void Wave_3(float deltaTime);
	void ChangeWave(StageWave wave);
	void CountMnager();

private:
	
	int endGr;
	int golGr;
	Scene nowScene;                      //���݂̃V�[��
	bool gameEnd;                        //�Q�[���G���h�i���j
	Input input; 
	StageWave nowSatge;
	int enemyDeadCount;                  //�G���S�J�E���g
	int cannonCount;                     //��������Ă���C����J�E���g
	int cannonGenerateCount;             //��C�����J�E���g

	EnemyGenerateManager m_EnemyManager; //�G�����N���X
	GameObjectManager* m_pGameManager;   //�Q�[���I�u�W�F�N�g�}�l�[�W���[

	Fps fps;                             //�Q�[�����ԊǗ�

};