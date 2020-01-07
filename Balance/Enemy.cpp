#include "Enemy.h"
#include "GamePlayManager.h"


Enemy::Enemy(const Vector2 & position, Vector2 velocity)
	:isDeadFlag(false),
	speed(5)
{
	_position = position;
	_size = Vector2(32,32);
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
	Move();
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
	isDeadFlag = true;
	GamePlayManager::Instance().EnemyDeadCountUp();    //プレイヤーに倒されたらカウントをUPさせる
}

void Enemy::Move()
{
	_position += m_Velocity * speed;
}
