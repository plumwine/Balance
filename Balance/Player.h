#pragma once
#include "Object.h"

//プレイヤークラス
class Player : public Object
{
public:
	Player(const Vector2 &position);
	~Player();
	//継承
	void Initialize() override;        //初期化
	void Draw() override;              //描画
	void Update(float deltaTime) override;            //更新
	void Release() override;           //解放
	bool IsDead() override;            //死亡判定
	void Hit(Object& object) override; //当たった時の処理
	
private:

	void Move(float deltaTime);        //移動
private:
	bool isDead;        //死亡判定（必要かは分からない）
	float speed;        //移動速度
	int input_x;
	int input_y;


};

