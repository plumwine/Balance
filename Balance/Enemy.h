#pragma once
#include "Object.h"

//敵クラス
class Enemy : public Object
{
public:
	Enemy(const Vector2& position, Vector2 velocity,int damage);
	~Enemy();


	void Initialize() override;        //初期化
	void Draw() override;              //描画
	void Update(float deltaTime) override;            //更新
	void Release() override;           //解放
	bool IsDead() override;            //死亡判定
	void Hit(Object& object) override; //当たった時の処理

private:

	void Move(float deltaTime);                       //移動方法
	void DeadJudgment();              //死亡判定
	void HpManager();
private:

	Vector2 m_Velocity;     //向く方向生成時に確認する
	Vector2 b_velocity;     //吹っ飛ぶ方向
	float speed;          //移動速度
	bool isDeadFlag;        //死亡判定
	int m_Hp;
	int m_Damage;

	
	float gravity;       //重力
};

