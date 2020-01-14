#include "Enemy.h"
#include "GamePlayManager.h"
#include <typeinfo.h>
#include "Cannon.h"
#include "Bullet.h"
#include "WindowInfo.h"


Enemy::Enemy(const Vector2 & position, Vector2 velocity)
	:isDeadFlag(false),
	speed(100)
{
	_position = position;
	_size = Vector2(30,30);
	m_Velocity = velocity;
	_grp = LoadGraph("../Texture/kari/enemy_A.png");
	Initialize();
}

Enemy::~Enemy()
{
}
//初期化
void Enemy::Initialize()
{
}
//描画
void Enemy::Draw()
{
	Render::Instance().RectDraw(*this);
}
//更新
void Enemy::Update(float deltaTime)
{
	Move(deltaTime);
	DeadJudgment();

}

void Enemy::Release()
{
}

bool Enemy::IsDead()
{
	return isDeadFlag;
}

void Enemy::Hit(Object & object)
{

	//現状判定する予定が弾と大砲だけなので、当たった時点で終了
	if (typeid(object) == typeid(Cannon) ||
		typeid(object) == typeid(Bullet))
	{
		GamePlayManager::Instance().EnemyDeadCountUp();    //プレイヤーに倒されたらカウントをUPさせる
		isDeadFlag = true;
		
	}
	
}

void Enemy::AreaHit(Object & object)
{
}

void Enemy::DeadJudgment()
{

	//ウィンドウ範囲外に出たら消す
	if (_position.x < -100 ||
		_position.x > WindowInfo::WindowWidth+100)
	{
		isDeadFlag = true;
	}
	if (_position.y < -100 ||
		_position.y > WindowInfo::WindowHeight+100)
	{
		isDeadFlag = true;
	}
}

void Enemy::Move(float deltaTime)
{
	_position += m_Velocity * speed* deltaTime;
}
