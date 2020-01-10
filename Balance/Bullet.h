#pragma once
#include "Object.h"

//’eƒNƒ‰ƒX
class Bullet:public Object
{
public:
	Bullet(const Vector2 &position,
		   Vector2 velocity);
	~Bullet();


	bool IsDead() override;                    //€‚ñ‚Å‚¢‚é‚©
	//Œp³
	void Initialize() override;        //‰Šú‰»
	void Draw() override;              //•`‰æ
	void Update(float deltaTime) override;            //XV
	void Release() override;           //‰ğ•ú
	void Hit(Object& object) override; //“–‚½‚Á‚½‚Ìˆ—
private:


	void Move(float deltaTime);                      //ˆÚ“®
	void DeadJudgment();              //€–S”»’è
	

private:
	Vector2 mVelocity; //ˆÚ“®•ûŒü
	float speed;       //‘¬‚³
	bool isDeadFlag;   //€‚ñ‚Å‚¢‚é‚©
};