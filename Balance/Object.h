#pragma once
#include "Vector2.h"

//	ゲームオブジェクトクラス
class Object
{
public:
	//	コンストラクタ
	Object() : _position(0, 0), _size(0, 0) {}

	//	初期化
	virtual void Initialize() = 0;

	//	描画
	virtual void Draw() = 0;

	//	更新
	virtual void Update() = 0;

	//	解放
	virtual void Release() = 0;

	//	メンバ関数にconstを付与する事で
	//	その関数内でのメンバ変数の変更を禁止にする
	Vector2 Position() const { return _position; }
	Vector2 Size() const { return _size; }

public:
	Vector2 _position;		//	座標
	Vector2 _size;			//	サイズ
};