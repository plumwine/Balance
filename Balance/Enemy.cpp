#include "Enemy.h"
#include "GamePlayManager.h"
#include <typeinfo.h>
#include "Cannon.h"
#include "Bullet.h"
#include "WindowInfo.h"
#include "Ground.h"


Enemy::Enemy(const Vector2 & position, Vector2 velocity, int damage)
	:isDeadFlag(false),
	speed(100),
	gravity(3)
{
	_position = position;
	_size = Vector2(30,30);
	m_Velocity = velocity;
	_grp = LoadGraph("../Texture/kari/enemy_A.png");
	m_Damage = damage + 1;     //012なので補正
	m_Hp = (damage + 1) * 2 - 1;//2n+1で135と上がっていく
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
	HpManager();
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
		//自分のHPを減らす
		m_Hp -= m_Damage;
	}
	if (typeid(object) == typeid(Ground))
	{
		isDeadFlag = true;
		GamePlayManager::Instance().EnemyDeadCountUp();    //プレイヤーに倒されたらカウントをUPさせる
	}

	
}

void Enemy::DeadJudgment()
{

	//ウィンドウ範囲外に出たら消す
	if (_position.x < -100 ||
		_position.x > WindowInfo::WindowWidth + 100)
	{
		GamePlayManager::Instance().EnemyDeadCountUp();    //プレイヤーに倒されたらカウントをUPさせる
		isDeadFlag = true;
	}
	if (_position.y < -100 ||
		_position.y > WindowInfo::WindowHeight + 100)
	{
		GamePlayManager::Instance().EnemyDeadCountUp();    //プレイヤーに倒されたらカウントをUPさせる
		isDeadFlag = true;
	}
}

void Enemy::HpManager()
{
	
}

void Enemy::Move(float deltaTime)
{
	//HPがなくなったら死亡
	if (m_Hp <= 0)
	{
		if (_direction == Direction::Left)
		{
			b_velocity = Vector2(50, -100);
		}

		if (_direction == Direction::Right)
		{
			b_velocity = Vector2(-50, -100);
		}
		//当たってるところを無しにする
		_direction = None;
		_position += b_velocity * speed * deltaTime;
		b_velocity.y += gravity;
	}
	else
	{
		_position += m_Velocity * speed* deltaTime;
	}
	
}
