#pragma once
#include "Object.h"
#include <stdio.h>

//��C�N���X
class Cannon : public Object
{
public:

	Cannon(const Vector2 &position,const Vector2 &size,const int grNum,int listNum);
	~Cannon();

	//�p��
	void Initialize() override;        //������
	void Draw() override;              //�`��
	void Update() override;            //�X�V
	void Release() override;           //���

private:

	//�Q�[���I������
	bool TouchGround();                //��C���n�ʂɂ������ǂ���
	void Move();                       //�ړ��֌W

private:
	bool underTouch;                   //�������ɑ�C�����邩�ǂ���
	bool flipHorizontal;               //�������]

	Vector2 velocity;                  //�ړ���
	int mListNum;                      //�����̔ԍ�
	int image;                         //�摜
	
};