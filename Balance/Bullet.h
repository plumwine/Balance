#pragma once
#include "Object.h"

//弾クラス
class Bullet:public Object
{
public:
	Bullet(const Vector2 &position,
		   Vector2 velocity);
	~Bullet();


	bool IsDead() override;                    //死んでいるか
	//継承
	void Initialize() override;        //初期化
	void Draw() override;              //描画
	void Update(float deltaTime) override;            //更新
	void Release() override;           //解放
	void Hit(Object& object) override; //当たった時の処理

public:



private:


	void Move(float deltaTime);        //移動
	void DeadJudgment();               //死亡判定
	

private:
	Vector2 mVelocity; //移動方向
	float speed;       //速さ
	bool isDeadFlag;   //死んでいるか
	float dis = 1000.0f;
};