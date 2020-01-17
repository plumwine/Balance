#pragma once
#include "Object.h"

//地面クラス、
class Ground : public Object
{
public:
	Ground(const Vector2 &position);
	~Ground();

	//継承
	void Initialize() override;        //初期化
	void Draw() override;              //描画
	void Update(float deltaTime) override;            //更新
	void Release() override;           //解放
	bool IsDead() override;            //死亡判定
	void Hit(Object& object) override; //当たった時の処理

	bool IsGameSet();                  //ゲーム終了フラグ

private:
	bool isGameEnd;                    //ゲームの終了判定


};

