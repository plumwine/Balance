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
//������
void Enemy::Initialize()
{
}
//�`��
void Enemy::Draw()
{
	Render::Instance().RectDraw(*this);
}
//�X�V
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
	//���󔻒肷��\�肪�e�Ƒ�C�����Ȃ̂ŁA�����������_�ŏI��
	isDeadFlag = true;
}

void Enemy::Move()
{
	_position += m_Velocity * speed;
}
