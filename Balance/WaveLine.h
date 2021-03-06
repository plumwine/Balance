#pragma once
#include "Object.h"

//到達ライン
class WaveLine : public Object
{

public:
	WaveLine(const Vector2 &position);
	~WaveLine();

	//継承
	void Initialize() override;        //初期化
	void Draw() override;              //描画
	void Update(float deltaTime) override;            //更新
	void Release() override;           //解放
	bool IsDead() override;            //死亡判定
	void Hit(Object& object) override; //当たった時の処理

	bool GetTouch();                   //触ったかどうかを知らせる


private:

	bool isTouch;    //大砲が触れたどうか
	Vector2 m_position;

};

