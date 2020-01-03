#include "Cannon.h"
#include"DxLib.h"
#include "Bullet.h"


//�R���X�g���N�^�@����������
Cannon::Cannon(const Vector2 &position, const Vector2 &size, GameObjectManager* objectManager, int listNum)
	:mListNum(listNum),
	underTouch(false),
	flipHorizontal(false)
{
	_position = position;
	_size = size;
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
	//
	DrawTurnGraph((int)(_position.x - _size.x / 2), (int)(_position.y - _size.y / 2),_grp, flipHorizontal);

}
//�X�V
void Cannon::Update(float deltaTime)
{
	Move();
	Shot();
	m_pObjectManager->Update(deltaTime);
	m_pObjectManager->Draw();

}
//���
void Cannon::Release()
{
}
bool Cannon::IsDead()
{
	return false;
}
//�������̓����蔻��
bool Cannon::TouchGround()
{
	return false;
}
//�ړ�
void Cannon::Move()
{


}

void Cannon::Shot()
{
	m_pObjectManager->Add(new Bullet(Vector2(100, 100), Vector2(32, 32), Vector2(1, 1)));
}
