#pragma once
#include "Object.h"
#include "GameObjectManager.h"

//大砲クラス
class Cannon : public Object
{
public:

	Cannon(const Vector2 &position,const Vector2 &size,GameObjectManager *objectManager,int listNum);
	~Cannon();

	//継承
	void Initialize() override;        //初期化
	void Draw() override;              //描画
	void Update(float deltaTime) override;            //更新
	void Release() override;           //解放
	bool IsDead() override;            //死亡判定
	void Shot();                       //弾を撃つ
private:

	//ゲーム終了判定
	bool TouchGround();                //大砲が地面についたかどうか
	void Move();                       //移動関係

	

private:
	bool underTouch;                   //下方向に大砲があるかどうか
	bool flipHorizontal;               //水平反転

	Vector2 velocity;                  //移動量
	int mListNum;                      //自分の番号
	GameObjectManager* m_pObjectManager;  //GameObjectManagerのポインタ
	
};