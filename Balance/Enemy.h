#pragma once
#include "Object.h"

//�G�N���X
class Enemy : public Object
{
public:
	Enemy(const Vector2& position, Vector2 velocity,int damage,bool rever);
	~Enemy();


	void Initialize() override;        //������
	void Draw() override;              //�`��
	void Update(float deltaTime) override;            //�X�V
	void Release() override;           //���
	bool IsDead() override;            //���S����
	void Hit(Object& object) override; //�����������̏���

private:

	void Move(float deltaTime);                       //�ړ����@
	void DeadJudgment();              //���S����
	void HpManager();
private:

	Vector2 m_Velocity;     //���������������Ɋm�F����
	Vector2 b_velocity;     //������ԕ���
	float speed;          //�ړ����x
	bool isDeadFlag;        //���S����
	int m_Hp;
	int m_Damage;
	bool isReverse;        //���]���邩�ǂ��� ����Ȃ�true
	float angle;

	float gravity;       //�d��
};

