#pragma once
#include <cmath>

// Vector2�N���X
class Vector2 {

public:
	//	�f�t�H���g�R���X�g���N�^
	Vector2();

	//	�����t���R���X�g���N�^
	Vector2(float x, float y);

	//�P�����Z�q�I�[�o�[���[�h
	Vector2 operator + ()const;
	Vector2 operator - ()const;

	//	���Z�q�I�[�o�[���[�h�u+�v
	Vector2 operator + (const Vector2& vec);

	//	���Z�q�I�[�o�[���[�h�u+=�v
	Vector2& operator += (const Vector2& vec);

	//	���Z�q�I�[�o�[���[�h�u-�v
	Vector2 operator - (const Vector2& vec);

	//	���Z�q�I�[�o�[���[�h�u-=�v
	Vector2& operator -= (const Vector2& vec);

	//	���Z�q�I�[�o�[���[�h�u*�v
	Vector2 operator*(const float & scale);

	//	���Z�q�I�[�o�[���[�h�u*=�v
	Vector2& operator *= (const Vector2& vec);

	//	���Z�q�I�[�o�[���[�h�u/�v
	Vector2 operator/(const float & scale);

	//	�x�N�g���̓���
	float Dot(const Vector2& vec);

	//	�x�N�g���̊O��
	float Cross(const Vector2& vec);

	//	�x�N�g���̒����擾
	float Magnitude();

	//	�x�N�g���̐��K��
	Vector2 Normalized();

public:
	float x;
	float y;
};