#include "GameObjectManager.h"
#include "Object.h"



GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
	//オブジェクトがnullになったらそのメモリを開放する
	for (auto& object : mObjects)
	{
		if (object != nullptr)
			delete object;
	}
	mObjects.clear();

}

void GameObjectManager::Update(float deltaTime)
{
	for (auto& object : mObjects)
	{
		if (object == nullptr) continue;
		if (!object->IsDead())
		{
			object->Update(deltaTime);
			for (auto& object_2 : mObjects)
			{
				if (object_2 == nullptr) continue;
				if (&object == &object_2) continue;
				if (object_2->IsDead()) continue;

				if (!object->RectCollision(*object_2)) continue;
				object->RectCollision(*object_2);
				object_2->RectCollision(*object);

			}
		}
			
	}

	auto itr = mObjects.begin();
	while (itr != mObjects.end())
	{
		if (*itr == nullptr)
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
	for (auto& object : mObjects)
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
	mObjects.emplace_back(pObject);
	pObject->Initialize();
}
