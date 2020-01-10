#pragma once
#include "Object.h"

//�v���C���[�N���X
class Player : public Object
{
public:
	Player(const Vector2 &position);
	~Player();
	//�p��
	void Initialize() override;        //������
	void Draw() override;              //�`��
	void Update(float deltaTime) override;            //�X�V
	void Release() override;           //���
	bool IsDead() override;            //���S����
	void Hit(Object& object) override; //�����������̏���
	
private:

	void Move(float deltaTime);        //�ړ�
private:
	bool isDead;        //���S����i�K�v���͕�����Ȃ��j
	float speed;        //�ړ����x
	int input_x;
	int input_y;


};

