#pragma once
#include "Object.h"

//�n�ʃN���X�A
class Ground : public Object
{
public:
	Ground(const Vector2 &position);
	~Ground();

	//�p��
	void Initialize() override;        //������
	void Draw() override;              //�`��
	void Update(float deltaTime) override;            //�X�V
	void Release() override;           //���
	bool IsDead() override;            //���S����
	void Hit(Object& object) override; //�����������̏���

	bool IsGameSet();                  //�Q�[���I���t���O

private:
	bool isGameEnd;                    //�Q�[���̏I������


};

