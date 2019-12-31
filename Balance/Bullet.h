#pragma once
#include "Object.h"
#include "Vector2.h"

//弾クラス
class Bullet:public Object
{
public:
	Bullet(const Vector2 &position, const Vector2 &size, const int grNum,
		   Vector2 velocity);
	~Bullet();


	bool IsDead();                    //死んでいるか
	//継承
	void Initialize() override;        //初期化
	void Draw() override;              //描画
	void Update() override;            //更新
	void Release() override;           //解放
	
private:
	

	void Move();                      //移動
	void DeadJudgment();              //死亡判定
	

private:
	Vector2 mVelocity; //移動方向
	float speed;       //速さ
	int image;         //画像
	bool isDeadFlag;   //死んでいるか
};