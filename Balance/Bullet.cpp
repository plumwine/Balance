#include "DxLib.h"
#include "Bullet.h"
#include "WindowInfo.h"




Bullet::Bullet(const Vector2 &position, const Vector2 &size, const int grNum, Vector2 velocity)
	:Object(position, size, grNum),
	mVelocity(velocity),
	speed(5),
	isDeadFlag(false)
{
	Initialize();
}


Bullet::~Bullet()
{
}

bool Bullet::IsDead()
{
	return false;
}

void Bullet::Initialize()
{
	//画像の描画
	image = LoadGraph("../Texture/kari/bullet_A.png");
}

void Bullet::Draw()
{
	DrawTurnGraph(_position.x - _size.x / 2, _position.y - _size.y / 2, image, false);
}

void Bullet::Update()
{
	Move();
	DeadJudgment();

}

void Bullet::Release()
{
	delete this;
}

void Bullet::Move()
{
	_position += mVelocity * speed;
}

void Bullet::DeadJudgment()
{

	//ウィンドウ範囲外に出たら消す
	if (_position.x < 0 ||
		_position.x > WindowInfo::WindowWidth)
	{
		isDeadFlag = true;
	}
	if (_position.y < 0 ||
		_position.y > WindowInfo::WindowHeight)
	{
		isDeadFlag = true;
	}

	//死亡判定が確定したら消す
	if (isDeadFlag)
	{
		Release();
	}


}
