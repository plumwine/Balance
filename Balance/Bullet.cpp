#include "DxLib.h"
#include "Bullet.h"
#include "WindowInfo.h"




Bullet::Bullet(const Vector2 &position, Vector2 velocity)
	:mVelocity(velocity),
	speed(5),
	isDeadFlag(false)
{
	_position = position;
	_size = Vector2(16, 16);
	_grp = LoadGraph("../Texture/kari/bullet_A.png");
	Initialize();
}


Bullet::~Bullet()
{
}

bool Bullet::IsDead()
{
	return isDeadFlag;
}

void Bullet::Initialize()
{
}

void Bullet::Draw()
{
	//Render::Instance().RectDraw(*this);
	DrawTurnGraph((int)(_position.x - _size.x / 2), (int)(_position.y - _size.y / 2), _grp, false);
}

void Bullet::Update(float deltaTime)
{
	Move();
	DeadJudgment();

}

void Bullet::Release()
{
}

void Bullet::Hit(Object & object)
{
	CurrentPosition(object);  //当たった方向への押し出し
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
}
