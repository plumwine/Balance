#pragma once
#include "Object.h"
#include "GameObjectManager.h"

//‘å–CƒNƒ‰ƒX
class Cannon : public Object
{
public:

	Cannon(const Vector2 &position,GameObjectManager *objectManager,int listNum);
	~Cannon();

	//Œp³
	void Initialize() override;        //‰Šú‰»
	void Draw() override;              //•`‰æ
	void Update(float deltaTime) override;            //XV
	void Release() override;           //‰ğ•ú
	bool IsDead() override;            //€–S”»’è
	void Hit(Object& object) override; //“–‚½‚Á‚½‚Ìˆ—
	void Shot();                       //’e‚ğŒ‚‚Â
private:

	void Move();                       //ˆÚ“®ŠÖŒW

	

private:
	bool underTouch;                   //‰º•ûŒü‚É‘å–C‚ª‚ ‚é‚©‚Ç‚¤‚©
	bool flipHorizontal;               //…•½”½“]
	bool isDeadFlag;

	Vector2 velocity;                  //ˆÚ“®—Ê
	float reaction;                    //”½“®
	float gravity;                     //d—Í

	int mListNum;                      //©•ª‚Ì”Ô†
	GameObjectManager* m_pObjectManager;  //GameObjectManager‚Ìƒ|ƒCƒ“ƒ^
	
};