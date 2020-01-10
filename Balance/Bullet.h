#pragma once
#include "Object.h"

//�e�N���X
class Bullet:public Object
{
public:
	Bullet(const Vector2 &position,
		   Vector2 velocity);
	~Bullet();


	bool IsDead() override;                    //����ł��邩
	//�p��
	void Initialize() override;        //������
	void Draw() override;              //�`��
	void Update(float deltaTime) override;            //�X�V
	void Release() override;           //���
	void Hit(Object& object) override; //�����������̏���
private:


	void Move(float deltaTime);                      //�ړ�
	void DeadJudgment();              //���S����
	

private:
	Vector2 mVelocity; //�ړ�����
	float speed;       //����
	bool isDeadFlag;   //����ł��邩
};