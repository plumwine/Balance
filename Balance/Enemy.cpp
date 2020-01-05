#include "Enemy.h"


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
//‰Šú‰»
void Enemy::Initialize()
{
}
//•`‰æ
void Enemy::Draw()
{
	Render::Instance().RectDraw(*this);
}
//XV
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
	//Œ»ó”»’è‚·‚é—\’è‚ª’e‚Æ‘å–C‚¾‚¯‚È‚Ì‚ÅA“–‚½‚Á‚½“_‚ÅI—¹
	isDeadFlag = true;
}

void Enemy::Move()
{
	_position += m_Velocity * speed;
}
