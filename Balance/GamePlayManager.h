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
	LoadScene,
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

	StageWave GetWave();
	//�X�R�A
	void ScoreUp();
	void GetPlayerPos(Vector2 pos);
private:
	//�V�[���Ǘ�
	void SceneUpdate(float deltaTime);
	void Load();
	void Title(float deltaTime);
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
	
	////�摜�֌W
	int title_Gr;                        //�^�C�g��
	int back_Gr_1;                         //�w�i�@��
	int back_Gr_2;                         //�w�i�@��
	int back_Gr_3;                         //�w�i�@��
	int result;                          //���U���g�w�i
	int endGr;                           //�G���f�B���O
	int golGr;                           //�G���f�B���O2
	int first;
	int second;
	int third;
	int scoreBack;
	//�e�L�X�g
	int gameplay_Text;                   //�Q�[���v���C
	int pushstart_Text;
	int title_Text;
	int score_Text;
	int rank_Text;

	int numberGr;                        //������
	int subNumGr;                        //������
	int gage_Gr;                         //�Q�[�W
	//�����Ǘ�
	//SE
	int boyon1;
	int hyun1;
	int button;
	//BGM
	int stageBGM;
	int titleBGM;
	int resultBGM;

	Scene nowScene;                      //���݂̃V�[��
	bool gameEnd;                        //�Q�[���G���h�i���j
	float waveline_Y;                    //WaveLine��Y������ɐ錾
	float topCannon_Y;                   //���݂̈�ԏ��Y���擾
	Input input; 
	StageWave nowSatge;
	int enemyDeadCount;                  //�G���S�J�E���g
	int cannonCount;                     //��������Ă���C����J�E���g
	int cannonGenerateCount;             //��C�����J�E���g

	int score;                           //�X�R�A
	Vector2 playerPos;                   //�v���C���[�̈ʒu

	EnemyGenerateManager m_EnemyManager; //�G�����N���X
	GameObjectManager* m_pGameManager;   //�Q�[���I�u�W�F�N�g�}�l�[�W���[

	Fps fps;                             //�Q�[�����ԊǗ�


	std::vector<int> ranking;
	bool addRankFlag;
};