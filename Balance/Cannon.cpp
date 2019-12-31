#include "Cannon.h"
#include"DxLib.h"


//�R���X�g���N�^�@����������
Cannon::Cannon(const Vector2 &position, const Vector2 &size, const int grNum, int listNum)
	:Object(position,size,grNum),
	mListNum(listNum),
	underTouch(false),
	flipHorizontal(false)
{
	Initialize();//������
}

Cannon::~Cannon()
{
}
//������
void Cannon::Initialize()
{
	//�摜�̕`��
	image = LoadGraph("../Texture/kari/battery_A.png");
}
//�`��
void Cannon::Draw()
{
	//
	DrawTurnGraph(_position.x - _size.x / 2, _position.y - _size.y / 2,image, flipHorizontal);

}
//�X�V
void Cannon::Update()
{
	Move();
}
//���
void Cannon::Release()
{
	//�������폜 �f�X�X�g���N�^���Ă�
	delete this;
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
