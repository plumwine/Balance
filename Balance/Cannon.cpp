#include "Cannon.h"
#include"DxLib.h"
#include "Bullet.h"


//コンストラクタ　初期化並び
Cannon::Cannon(const Vector2 &position, const Vector2 &size, GameObjectManager* objectManager, int listNum)
	:mListNum(listNum),
	underTouch(false),
	flipHorizontal(false)
{
	_position = position;
	_size = size;
	m_pObjectManager = objectManager;
	_grp = LoadGraph("../Texture/kari/battery_A.png");
	

	Initialize();//初期化
}

Cannon::~Cannon()
{
}
//初期化
void Cannon::Initialize()
{
}
//描画
void Cannon::Draw()
{
	//
	DrawTurnGraph((int)(_position.x - _size.x / 2), (int)(_position.y - _size.y / 2),_grp, flipHorizontal);

}
//更新
void Cannon::Update(float deltaTime)
{
	Move();
	Shot();
	m_pObjectManager->Update(deltaTime);
	m_pObjectManager->Draw();

}
//解放
void Cannon::Release()
{
}
bool Cannon::IsDead()
{
	return false;
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

void Cannon::Shot()
{
	m_pObjectManager->Add(new Bullet(Vector2(100, 100), Vector2(32, 32), Vector2(1, 1)));
}
