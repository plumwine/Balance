#include "GameObjectManager.h"
#include <typeinfo.h>


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

	//pObject->Initialize();
}
