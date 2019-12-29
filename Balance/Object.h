#pragma once
#include "Vector2.h"

//	�Q�[���I�u�W�F�N�g�N���X
class Object
{
public:
	//	�R���X�g���N�^
	Object() : _position(0, 0), _size(0, 0) {}

	//	������
	virtual void Initialize() = 0;

	//	�`��
	virtual void Draw() = 0;

	//	�X�V
	virtual void Update() = 0;

	//	���
	virtual void Release() = 0;

	//	�����o�֐���const��t�^���鎖��
	//	���̊֐����ł̃����o�ϐ��̕ύX���֎~�ɂ���
	Vector2 Position() const { return _position; }
	Vector2 Size() const { return _size; }

public:
	Vector2 _position;		//	���W
	Vector2 _size;			//	�T�C�Y
};