#include "Cannon.h"
#include "DxLib.h"
#include "Bullet.h"
#include "Enemy.h"
#include <typeinfo.h>


//�R���X�g���N�^�@����������
Cannon::Cannon(const Vector2 &position, GameObjectManager* objectManager, int listNum)
	:mListNum(listNum),
	underTouch(false),
	flipHorizontal(false),
	isDeadFlag(false)
{
	_position = position;
	_size = Vector2(32, 32);
	m_pObjectManager = objectManager;
	_grp = LoadGraph("../Texture/kari/battery_A.png");
	

	Initialize();//������
}

Cannon::~Cannon()
{
}
//������
void Cannon::Initialize()
{
}
//�`��
void Cannon::Draw()
{
	//�ŏ��͉E����
	Render::Instance().RectDraw(*this, flipHorizontal);
}
//�X�V
void Cannon::Update(float deltaTime)
{
	Shot();
	Move();
	m_pObjectManager->Update(deltaTime);
	m_pObjectManager->Draw();

}
//���
void Cannon::Release()
{
}
bool Cannon::IsDead()
{
	return isDeadFlag;
}
void Cannon::Hit(Object & object)
{
	//�e�Ɋւ��Ă͓����蔻������Ȃ�
	if (typeid(object) == typeid(Bullet)) return;

	CurrentPosition(object);  //�������������ւ̉����o��
	//���������̂��G�Ȃ�
	if (typeid(object) == typeid(Enemy))
	{
		isDeadFlag = true;
	}
	


}
//�ړ�
void Cannon::Move()
{
	//�G�E�e�ȊO�̃I�u�W�F�N�g�̏�ɏ������
	if (_direction == Direction::Bottom)
	{
		gravity = 0;
	}
	else
	{
		gravity = 2.0f;
	}
	velocity.x = reaction;  //�������̈ړ��i�d�́j
	velocity.y = gravity;   //�c�����ւ̈ړ�


	_position += velocity;
	velocity = Vector2(0, 0);
	reaction = 0;
}

void Cannon::Shot()
{
	//�Q�[���p�b�h�̉����ꂽ�{�^���ɍ��킹�Ĕ���������
	
	//m_pObjectManager->Add(new Bullet(Vector2(100, 100), Vector2(32, 32), Vector2(1, 1)));
}
