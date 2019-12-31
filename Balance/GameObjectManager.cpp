#include "GameObjectManager.h"
#include "Object.h"
#include "Render.h"



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
}

void GameObjectManager::Draw(Render * pRender)
{
	for (auto& object : mObjects)
	{
		//オブジェクトがnullならcontinue
		if (object == nullptr) continue;
		//オブジェクトが生きていたら描画する
		//if()
	}
}
//追加
void GameObjectManager::Add(Object * pObject)
{
	mObjects.emplace_back(pObject);
	pObject->Initialize();
}
