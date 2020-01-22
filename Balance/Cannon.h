#pragma once
#include "Object.h"
#include "GameObjectManager.h"
#include "Input.h"

//��C�N���X
class Cannon : public Object
{
public:

	Cannon(const Vector2 &position,GameObjectManager *objectManager,int num);
	~Cannon();

	//�p��
	void Initialize() override;        //������
	void Draw() override;              //�`��
	void Update(float deltaTime) override;  //�X�V
	void Release() override;           //���
	bool IsDead() override;            //���S����
	void Hit(Object& object) override; //�����������̏���

	int GetNowNum();                   //���݂̏���
	void GetObj(Object* obj);

	void Shot(float deltaTime);                       //�e������
private:

	void Move(float deltaTime);        //�ړ��֌W

private:
	bool underTouch;                   //�������ɑ�C���v���C���[�����邩�ǂ���
	bool flipHorizontal;               //�������]
	bool isDeadFlag;

	float reaction;                    //����
	float gravity;                     //�d��
	float centerPosX;                  //���S�ʒuX
	int nowNum;                        //����Y���W
	Input input;
	Vector2 enemyDir;                  //�G�̕���
	//��
	int shot_se;                       //���Ƃ��̉�
	int shotWaitTime;
	int maxShotWaitTime;
	





	//�A�j���[�V�����p
	float animTime;
	float maxAnimTime;
	int animNum;
	int maxAnimNum;
	Object* m_pObj;
	GameObjectManager* m_pObjectManager;  //GameObjectManager�̃|�C���^
};