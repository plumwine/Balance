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


	//	��`�΋�`�̔���
	bool RectCollision(const Object& rect)
	{
		Vector2 rectAPos = Position();
		Vector2 rectBPos = rect.Position();
		Vector2 rectASize = Size();
		Vector2 rectBSize = rect.Size();
		auto dx = abs((rectAPos.x + rectASize.x / 2) - (rectBPos.x + rectBSize.x / 2));
		auto dy = abs((rectAPos.y + rectASize.y / 2) - (rectBPos.y + rectBSize.y / 2));

		return (dx < (rectASize.x + rectBSize.x) / 2 && dy < (rectASize.y + rectBSize.y) / 2);
	}

	//	�����o�֐���const��t�^���鎖��
	//	���̊֐����ł̃����o�ϐ��̕ύX���֎~�ɂ���
	Vector2 Position() const { return _position; }
	Vector2 Size() const { return _size; }
	int Grp() const { return _grp; }

protected:
	Vector2 _position;		//	���W
	Vector2 _size;			//	�T�C�Y
	int _grp;				//  �摜ID
};