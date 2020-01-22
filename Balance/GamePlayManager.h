#pragma once
#include "GameObjectManager.h"
#include "Input.h"
#include "EnemyGenerateManager.h"
#include "FPS.h"

//ゲーム循環enum
enum Scene
{
	TitleScene,
	GamePlayScene,
	EndScene,
	LoadScene,
};


//ゲームプレイ用
enum StageWave
{
	Stage1,
	Stage2,
	Stage3
};


//	ゲームプレイ管理クラス
class GamePlayManager
{
private:
	GamePlayManager() { Initialize(); }
	GamePlayManager(const GamePlayManager&) { Initialize(); }
	GamePlayManager& operator=(const GamePlayManager&) {}
public:

	//	インスタンスを取得
	static GamePlayManager& Instance();
	~GamePlayManager();

	void Initialize(); //初期化

	//	ループ処理
	void Update();
	//仮
	void endGame() { gameEnd = true; }

	//  更新処理
	void GameUpdate(float deltaTime);
	void EnemyDeadCountUp() { enemyDeadCount++; };       //敵死亡カウントUP
	void DeadCannon() { cannonCount--; }
	int GetCannonCount() { return cannonCount; }         //砲台の生きている数

	StageWave GetWave();
	//スコア
	void ScoreUp();
	void GetPlayerPos(Vector2 pos);
	void SetWaveClear();
private:
	//シーン管理
	void SceneUpdate(float deltaTime);
	void Load();
	void Title(float deltaTime);
	void Ending();
	void ChangeScene(Scene scene);
	void Init();

	//Wave
	void WaveUpdate(float deltaTime);

	//ウェイブ管理
	void Wave_1(float deltaTime);
	void Wave_2(float deltaTime);
	void Wave_3(float deltaTime);
	void ChangeWave(StageWave wave);
	void CountMnager();

	void TimeLimitManager(float deltaTime);
	

private:
	
	////画像関係
	int title_Gr;                        //タイトル
	int back_Gr_1;                         //背景　朝
	int back_Gr_2;                         //背景　昼
	int back_Gr_3;                         //背景　夜
	int result;                          //リザルト背景
	int endGr;                           //エンディング
	int golGr;                           //エンディング2
	//Wave
	int wave_1;
	int wave_2;
	int wave_3;
	//説明
	int idou_Tu;
	int endClear_Tu;
	int generate_Tu;                    
	int shot_Tu;
	int first;
	int second;
	int third;
	int scoreBack;
	//テキスト
	int gameplay_Text;                   //ゲームプレイ
	int pushstart_Text;
	int title_Text;
	int score_Text;
	int rank_Text;

	int numberGr;                        //数字大
	int subNumGr;                        //数字小
	int gage_Gr;                         //ゲージ
	//音源管理
	//SE
	int boyon1;
	int hyun1;
	int button;
	//BGM
	int stageBGM;
	int titleBGM;
	int resultBGM;

	Scene nowScene;                      //現在のシーン
	bool gameEnd;                        //ゲームエンド（仮）
	bool waveClear;
	float waveline_Y;                    //WaveLineのYを勝手に宣言
	float topCannon_Y;                   //現在の一番上のYを取得
	Input input; 
	StageWave nowSatge;
	int enemyDeadCount;                  //敵死亡カウント
	int cannonCount;                     //生成されている砲台をカウント
	int cannonGenerateCount;             //大砲生成カウント

	int geneWaitTime;
	int maxGeneWaitTime;

	//数字
	float timeLimit;                     //時間制限

	int score;                           //スコア
	Vector2 playerPos;                   //プレイヤーの位置

	EnemyGenerateManager m_EnemyManager; //敵生成クラス
	GameObjectManager* m_pGameManager;   //ゲームオブジェクトマネージャー

	Fps fps;                             //ゲーム時間管理
	bool isSousa;                        //操作説明を出すかどうか


	std::vector<int> ranking;
	bool addRankFlag;
};