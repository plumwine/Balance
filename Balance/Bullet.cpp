#include "DxLib.h"
#include "Bullet.h"
#include "WindowInfo.h"
#include "Enemy.h"
#include "Player.h"
#include "Cannon.h"

Bullet::Bullet(const Vector2 &position, Vector2 velocity)
	:isDeadFlag(false),
	speed(500)
{
	_position = position;
	_size = Vector2(16, 16);
	mVelocity = velocity;
	_grp = LoadGraph("../Texture/master/Hane.png");
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
	Render::Instance().RectDraw(*this);
}

void Bullet::Update(float deltaTime)
{
	Move(deltaTime);
	DeadJudgment();

}

void Bullet::Release()
{
}

void Bullet::Hit(Object & object)
{
	if (typeid(object) == typeid(Cannon) ||
		typeid(object) == typeid(Player) ||
		typeid(object) == typeid(Bullet))
	{
		return;
	}
		
	if (typeid(object) == typeid(Enemy))
	{
		isDeadFlag = true;
	}

}



void Bullet::Move(float deltaTime)
{
	_position += mVelocity * speed * deltaTime;
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
