#include "GameObjectManager.h"
#include "Object.h"
#include "Render.h"



GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
	//�I�u�W�F�N�g��null�ɂȂ����炻�̃��������J������
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
		//�I�u�W�F�N�g��null�Ȃ�continue
		if (object == nullptr) continue;
		//�I�u�W�F�N�g�������Ă�����`�悷��
		//if()
	}
}
//�ǉ�
void GameObjectManager::Add(Object * pObject)
{
	mObjects.emplace_back(pObject);
	pObject->Initialize();
}
