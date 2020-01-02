#pragma once
#include "Object.h"
#include "Vector2.h"

//’eƒNƒ‰ƒX
class Bullet:public Object
{
public:
	Bullet(const Vector2 &position, const Vector2 &size,
		   Vector2 velocity);
	~Bullet();


	bool IsDead() override;                    //€‚ñ‚Å‚¢‚é‚©
	//Œp³
	void Initialize() override;        //‰Šú‰»
	void Draw() override;              //•`‰æ
	void Update(float deltaTime) override;            //XV
	void Release() override;           //‰ğ•ú
	
private:
	

	void Move();                      //ˆÚ“®
	void DeadJudgment();              //€–S”»’è
	

private:
	Vector2 mVelocity; //ˆÚ“®•ûŒü
	float speed;       //‘¬‚³
	bool isDeadFlag;   //€‚ñ‚Å‚¢‚é‚©
};