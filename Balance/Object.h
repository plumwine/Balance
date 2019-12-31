#pragma once
#include "Vector2.h"

enum Direction
{
	Top, Bottom, Right, Left, None
};

//	ゲームオブジェクトクラス
class Object
{
public:
	//	コンストラクタ
	Object(Vector2 position, Vector2 size, int grNum);

	//	初期化
	virtual void Initialize();

	//	描画
	virtual void Draw();

	//	更新
	virtual void Update();

	//	解放
	virtual void Release();


	//	矩形対矩形の判定
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

	//	メンバ関数にconstを付与する事で
	//	その関数内でのメンバ変数の変更を禁止にする
	Vector2 Position() const { return _position; }
	Vector2 Size() const { return _size; }
	int Grp() const { return _grp; }

protected:
	Vector2 _position;		//	座標
	Vector2 _size;			//	サイズ
	int _grp;				//  画像ID
	Direction _direction;   //  当たった方向
};