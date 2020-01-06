#pragma once
#include "Object.h"
#include "GameObjectManager.h"

//��C�N���X
class Cannon : public Object
{
public:

	Cannon(const Vector2 &position,GameObjectManager *objectManager,int listNum);
	~Cannon();

	//�p��
	void Initialize() override;        //������
	void Draw() override;              //�`��
	void Update(float deltaTime) override;            //�X�V
	void Release() override;           //���
	bool IsDead() override;            //���S����
	void Hit(Object& object) override; //�����������̏���
	void Shot();                       //�e������
private:

	void Move();                       //�ړ��֌W

	

private:
	bool underTouch;                   //�������ɑ�C�����邩�ǂ���
	bool flipHorizontal;               //�������]
	bool isDeadFlag;

	Vector2 velocity;                  //�ړ���
	float reaction;                    //����
	float gravity;                     //�d��

	int mListNum;                      //�����̔ԍ�
	GameObjectManager* m_pObjectManager;  //GameObjectManager�̃|�C���^
	
};