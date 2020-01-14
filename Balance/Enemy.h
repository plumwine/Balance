#pragma once
#include "Object.h"

//�G�N���X
class Enemy : public Object
{
public:
	Enemy(const Vector2& position, Vector2 velocity);
	~Enemy();


	void Initialize() override;        //������
	void Draw() override;              //�`��
	void Update(float deltaTime) override;            //�X�V
	void Release() override;           //���
	bool IsDead() override;            //���S����
	void Hit(Object& object) override; //�����������̏���
	void AreaHit(Object & object) override;

private:

	void Move(float deltaTime);                       //�ړ����@
	void DeadJudgment();              //���S����
private:

	Vector2 m_Velocity;     //���������������Ɋm�F����
	float speed;          //�ړ����x
	bool isDeadFlag;        //���S����


};

