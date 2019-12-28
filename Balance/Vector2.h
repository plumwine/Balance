#pragma once
#include <cmath>

// Vector2クラス
class Vector2 {

public:
	//	デフォルトコンストラクタ
	Vector2();

	//	引数付きコンストラクタ
	Vector2(float x, float y);

	//単項演算子オーバーロード
	Vector2 operator + ()const;
	Vector2 operator - ()const;

	//	演算子オーバーロード「+」
	Vector2 operator + (const Vector2& vec);

	//	演算子オーバーロード「+=」
	Vector2& operator += (const Vector2& vec);

	//	演算子オーバーロード「-」
	Vector2 operator - (const Vector2& vec);

	//	演算子オーバーロード「-=」
	Vector2& operator -= (const Vector2& vec);

	//	演算子オーバーロード「*」
	Vector2 operator*(const float & scale);

	//	演算子オーバーロード「*=」
	Vector2& operator *= (const Vector2& vec);

	//	演算子オーバーロード「/」
	Vector2 operator/(const float & scale);

	//	ベクトルの内積
	float Dot(const Vector2& vec);

	//	ベクトルの外積
	float Cross(const Vector2& vec);

	//	ベクトルの長さ取得
	float Magnitude();

	//	ベクトルの正規化
	Vector2 Normalized();

public:
	float x;
	float y;
};