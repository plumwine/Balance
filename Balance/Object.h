#pragma once
#include "Vector2.h"

enum Direction
{
	Top, Bottom, Right, Left, None
};

//	�Q�[���I�u�W�F�N�g�N���X
class Object
{
public:
	//	�R���X�g���N�^
	Object(Vector2 position, Vector2 size, int grNum);

	//	������
	virtual void Initialize();

	//	�`��
	virtual void Draw();

	//	�X�V
	virtual void Update();

	//	���
	virtual void Release();


	//	��`�΋�`�̔���
	bool RectCollision(const Object& rect)
	{
		Vector2 rectAPos = Position();
		Vector2 rectBPos = rect.Position();
		Vector2 rectASize = Size();
		Vector2 rectBSize = rect.Size();
		auto dx = (rectAPos.x + rectASize.x / 2) - (rectBPos.x + rectBSize.x / 2);
		auto dy = (rectAPos.y + rectASize.y / 2) - (rectBPos.y + rectBSize.y / 2);

		if (abs(dx) < (rectASize.x + rectBSize.x) / 2 && abs(dy) < (rectASize.y + rectBSize.y) / 2)
		{
			_direction = ColDirection(Vector2(dx, dy), rectBSize);
			return true;
		}
		_direction = None;
	}

	Direction ColDirection(Vector2 dir, Vector2 otherSize)
	{
		Vector2 AddSize = _size + otherSize;

		float x = dir.x / AddSize.x;
		float y = dir.y / AddSize.y;

		if (abs(x) > abs(y))
		{
			if (x < 0)
			{
				return Left;
			}
			return Right;
		}

		if (y < 0)
		{
			return Bottom;
		}
		return Top;
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
	Direction _direction;   //  ������������
};