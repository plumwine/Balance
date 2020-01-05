#pragma once
#include "Object.h"
#include "GameObjectManager.h"

//‘å–CƒNƒ‰ƒX
class Cannon : public Object
{
public:

	Cannon(const Vector2 &position,const Vector2 &size,GameObjectManager *objectManager,int listNum);
	~Cannon();

	//Œp³
	void Initialize() override;        //‰Šú‰»
	void Draw() override;              //•`‰æ
	void Update(float deltaTime) override;            //XV
	void Release() override;           //‰ğ•ú
	bool IsDead() override;            //€–S”»’è
	void Shot();                       //’e‚ğŒ‚‚Â
private:

	//ƒQ[ƒ€I—¹”»’è
	bool TouchGround();                //‘å–C‚ª’n–Ê‚É‚Â‚¢‚½‚©‚Ç‚¤‚©
	void Move();                       //ˆÚ“®ŠÖŒW

	

private:
	bool underTouch;                   //‰º•ûŒü‚É‘å–C‚ª‚ ‚é‚©‚Ç‚¤‚©
	bool flipHorizontal;               //…•½”½“]

	Vector2 velocity;                  //ˆÚ“®—Ê
	int mListNum;                      //©•ª‚Ì”Ô†
	GameObjectManager* m_pObjectManager;  //GameObjectManager‚Ìƒ|ƒCƒ“ƒ^
	
};