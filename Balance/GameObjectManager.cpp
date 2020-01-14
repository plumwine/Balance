#include "GameObjectManager.h"
#include <typeinfo.h>
#include "Enemy.h"
#include "Bullet.h"
#include "Cannon.h"
#include "Player.h"


GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
	//追加するオブジェクトが残っていたら、オブジェクトを削除しメモリを開放する
	for (auto ptr : m_addObjectList)
	{
		if (ptr != nullptr)
		{
			delete ptr;
		}
	}
	m_addObjectList.clear();

	//オブジェクトがnullになったらそのメモリを開放する
	for (auto object : mObjects)
	{
		if (object != nullptr)
			delete object;
	}
	mObjects.clear();
}

void GameObjectManager::Update(float deltaTime)
{
	for (auto ptr : m_addObjectList)
	{
		mObjects.emplace_back(ptr);
		ptr->Initialize();
	}
	m_addObjectList.clear();


	//オブジェクト管理
	for (auto object : mObjects)
	{
		if (object == nullptr) continue;
		if (!object->IsDead())
		{

			object->Update(deltaTime);
			for (auto object_2 : mObjects)
			{
				if (object_2 == nullptr) continue;
				if (object == object_2) continue;
				if (object_2->IsDead()) continue;

				if (object->RectCollision(*object_2))
				{
					object->Hit(*object_2);
					object_2->Hit(*object);

				}
			}
		}
	}

	//enemyDir();
	
		
	


	TopCannon();


	//削除
	auto itr = mObjects.begin();
	while (itr != mObjects.end())
	{


		if (*itr == nullptr || (*itr)->IsDead())
		{
			itr = mObjects.erase(itr);

		}
		else
		{
			itr++;
		}
	}
}

void GameObjectManager::Draw()
{
	for (auto object : mObjects)
	{
		//オブジェクトがnullならcontinue
		if (object == nullptr) continue;


		//オブジェクトが生きていたら描画する
		if (!object->IsDead())
		{
			object->Draw();
		}
		else
		{
			continue;
		}

	}
}
//追加
void GameObjectManager::Add(Object * pObject)
{
	m_addObjectList.emplace_back(pObject);

}

void GameObjectManager::enemyDir()
{
	//敵以外ならcontinue
	for (auto enemies : mObjects)
	{
		int dis = 1000;
		if (enemies == nullptr) continue;
		if (enemies->IsDead()) continue;
		Enemy* ene = dynamic_cast<Enemy*>(enemies);
		//弾の方向
		for (auto bullets : mObjects)
		{
		    if (bullets == nullptr) continue;
		    if (bullets->IsDead()) continue;
			Bullet* bul = dynamic_cast<Bullet *>(bullets);

		    
		    float dis_2 = bul->Position().x - ene->Position().x + bul->Position().y - ene->Position().y;
		    
		    if (dis >= dis_2)
		    {
		    	dis = dis_2;
		    	//敵の検知
		    	bul->AreaHit(*ene);
		    }
		}
	}
}


//一番上のCannonのX座標の取得
float GameObjectManager::TopCannon()
{

	int Topnum = 1;
	float Top_X = 900;
	for (auto cannon : mObjects)
	{
		if (cannon == nullptr) continue;
		if (cannon->IsDead()) continue;

		//型をキャストして、nullにならなかったものがtopとする
		Cannon* a = dynamic_cast<Cannon*>(cannon);
		if (a != nullptr)
		{
			if (Topnum <= a->GetNowNum())
			{
				Topnum = a->GetNowNum();
				Top_X = a->Position().x;
			}
		}
	}
	return Top_X;
}
