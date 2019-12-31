#pragma once
#include "Object.h"
#include "Vector2.h"

//�e�N���X
class Bullet:public Object
{
public:
	Bullet(const Vector2 &position, const Vector2 &size, const int grNum,
		   Vector2 velocity);
	~Bullet();


	bool IsDead();                    //����ł��邩
	//�p��
	void Initialize() override;        //������
	void Draw() override;              //�`��
	void Update() override;            //�X�V
	void Release() override;           //���
	
private:
	

	void Move();                      //�ړ�
	void DeadJudgment();              //���S����
	

private:
	Vector2 mVelocity; //�ړ�����
	float speed;       //����
	int image;         //�摜
	bool isDeadFlag;   //����ł��邩
};