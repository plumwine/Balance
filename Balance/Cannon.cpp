#include "Cannon.h"
#include"DxLib.h"


//コンストラクタ　初期化並び
Cannon::Cannon(const Vector2 &position, const Vector2 &size, const int grNum, int listNum)
	:Object(position,size,grNum),
	mListNum(listNum),
	underTouch(false),
	flipHorizontal(false)
{
	Initialize();//初期化
}

Cannon::~Cannon()
{
}
//初期化
void Cannon::Initialize()
{
	//画像の描画
	image = LoadGraph("../Texture/kari/battery_A.png");
}
//描画
void Cannon::Draw()
{
	//
	DrawTurnGraph(_position.x - _size.x / 2, _position.y - _size.y / 2,image, flipHorizontal);

}
//更新
void Cannon::Update()
{
	Move();
}
//解放
void Cannon::Release()
{
	//自分を削除 デスストラクタを呼ぶ
	delete this;
}
//下方向の当たり判定
bool Cannon::TouchGround()
{
	return false;
}
//移動
void Cannon::Move()
{


}
