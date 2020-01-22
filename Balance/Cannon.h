#pragma once
#include "Object.h"
#include "GameObjectManager.h"
#include "Input.h"

//大砲クラス
class Cannon : public Object
{
public:

	Cannon(const Vector2 &position,GameObjectManager *objectManager,int num);
	~Cannon();

	//継承
	void Initialize() override;        //初期化
	void Draw() override;              //描画
	void Update(float deltaTime) override;  //更新
	void Release() override;           //解放
	bool IsDead() override;            //死亡判定
	void Hit(Object& object) override; //当たった時の処理

	int GetNowNum();                   //現在の順番
	void GetObj(Object* obj);

	void Shot(float deltaTime);                       //弾を撃つ
private:

	void Move(float deltaTime);        //移動関係

private:
	bool underTouch;                   //下方向に大砲かプレイヤーがあるかどうか
	bool flipHorizontal;               //水平反転
	bool isDeadFlag;

	float reaction;                    //反動
	float gravity;                     //重力
	float centerPosX;                  //中心位置X
	int nowNum;                        //今のY座標
	Input input;
	Vector2 enemyDir;                  //敵の方向
	//音
	int shot_se;                       //撃つときの音
	int shotWaitTime;
	int maxShotWaitTime;
	





	//アニメーション用
	float animTime;
	float maxAnimTime;
	int animNum;
	int maxAnimNum;
	Object* m_pObj;
	GameObjectManager* m_pObjectManager;  //GameObjectManagerのポインタ
};