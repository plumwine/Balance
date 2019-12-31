#pragma once
#include "Object.h"
#include <stdio.h>

//‘å–CƒNƒ‰ƒX
class Cannon : public Object
{
public:

	Cannon(Vector2 &position, Vector2 &size,int num);
	~Cannon();

	//Œp³
	void Initialize() override;        //‰Šú‰»
	void Draw() override;              //•`‰æ
	void Update() override;            //XV
	void Release() override;           //‰ğ•ú

private:

	//ƒQ[ƒ€I—¹”»’è
	bool TouchGround();                //‘å–C‚ª’n–Ê‚É‚Â‚¢‚½‚©‚Ç‚¤‚©
	void Move();                       //ˆÚ“®ŠÖŒW

private:
	bool underTouch;                   //‰º•ûŒü‚É‘å–C‚ª‚ ‚é‚©‚Ç‚¤‚©
	bool flipHorizontal;               //…•½”½“]

	Vector2 velocity;                  //ˆÚ“®—Ê
	int mListNum;                      //©•ª‚Ì”Ô†
	int image;                         //‰æ‘œ
	
};