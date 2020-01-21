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
	m_Damage = damage + 1;     //012�Ȃ̂ŕ␳
	m_Hp = (damage + 1) * 2 - 1;//2n+1��135�Əオ���Ă���
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
	
	//���󔻒肷��\�肪�e�Ƒ�C�����Ȃ̂ŁA�����������_�ŏI��
	if (typeid(object) == typeid(Cannon) ||
		typeid(object) == typeid(Bullet))
	{
		//������HP�����炷
		m_Hp -= m_Damage;
	}
	if (typeid(object) == typeid(Ground))
	{
		isDeadFlag = true;
		GamePlayManager::Instance().EnemyDeadCountUp();    //�v���C���[�ɓ|���ꂽ��J�E���g��UP������
	}

	
}

void Enemy::DeadJudgment()
{

	//�E�B���h�E�͈͊O�ɏo�������
	if (_position.x < -100 ||
		_position.x > WindowInfo::WindowWidth + 100)
	{
		GamePlayManager::Instance().EnemyDeadCountUp();    //�v���C���[�ɓ|���ꂽ��J�E���g��UP������
		isDeadFlag = true;
	}
	if (_position.y < -100 ||
		_position.y > WindowInfo::WindowHeight + 100)
	{
		GamePlayManager::Instance().EnemyDeadCountUp();    //�v���C���[�ɓ|���ꂽ��J�E���g��UP������
		isDeadFlag = true;
	}
}

void Enemy::HpManager()
{
	
}

void Enemy::Move(float deltaTime)
{
	//HP���Ȃ��Ȃ����玀�S
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
		//�������Ă�Ƃ���𖳂��ɂ���
		_direction = None;
		_position += b_velocity * speed * deltaTime;
		b_velocity.y += gravity;
	}
	else
	{
		_position += m_Velocity * speed* deltaTime;
	}
	
}
