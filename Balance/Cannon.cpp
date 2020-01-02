#include "Cannon.h"
#include"DxLib.h"


//�R���X�g���N�^�@����������
Cannon::Cannon(const Vector2 &position, const Vector2 &size, int listNum)
	:mListNum(listNum),
	underTouch(false),
	flipHorizontal(false)
{
	_position = position;
	_size = size;
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
}
//���
void Cannon::Release()
{
	//�������폜 �f�X�X�g���N�^���Ă�
	delete this;
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
