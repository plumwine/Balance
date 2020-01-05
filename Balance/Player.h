#pragma once
#include "Object.h"
#include "GameObjectManager.h"
#include "Input.h"

//�v���C���[�N���X
class Player : public Object
{
public:
	Player(const Vector2 &position,GameObjectManager*objectManager);
	~Player();

	//�p��
	void Initialize() override;        //������
	void Draw() override;              //�`��
	void Update(float deltaTime) override;            //�X�V
	void Release() override;           //���
	bool IsDead() override;            //���S����
	void Hit(Object& object) override; //�����������̏���

	
private:

	void Move();        //�ړ�
	void Generate();    //��C�𐶐�
private:
	bool isDead;        //���S����i�K�v���͕�����Ȃ��j
	float speed;        //�ړ����x
	int input_x;
	int input_y;
	Vector2 veclocity;
	GameObjectManager* m_pObjectManager; 


};

