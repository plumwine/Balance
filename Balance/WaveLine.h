#pragma once
#include "Object.h"

//“’Bƒ‰ƒCƒ“
class WaveLine : public Object
{

public:
	WaveLine(const Vector2 &position);
	~WaveLine();

	//Œp³
	void Initialize() override;        //‰Šú‰»
	void Draw() override;              //•`‰æ
	void Update(float deltaTime) override;            //XV
	void Release() override;           //‰ğ•ú
	bool IsDead() override;            //€–S”»’è
	void Hit(Object& object) override; //“–‚½‚Á‚½‚Ìˆ—
	void AreaHit(Object & object) override;

	bool GetTouch();                   //G‚Á‚½‚©‚Ç‚¤‚©‚ğ’m‚ç‚¹‚é


private:

	bool isTouch;    //‘å–C‚ªG‚ê‚½‚Ç‚¤‚©
	Vector2 m_position;

};

