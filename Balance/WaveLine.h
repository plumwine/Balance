#pragma once
#include "Object.h"

//���B���C��
class WaveLine : public Object
{

public:
	WaveLine(const Vector2 &position);
	~WaveLine();

	//�p��
	void Initialize() override;        //������
	void Draw() override;              //�`��
	void Update(float deltaTime) override;            //�X�V
	void Release() override;           //���
	bool IsDead() override;            //���S����
	void Hit(Object& object) override; //�����������̏���
	void AreaHit(Object & object) override;

	bool GetTouch();                   //�G�������ǂ�����m�点��


private:

	bool isTouch;    //��C���G�ꂽ�ǂ���
	Vector2 m_position;

};

