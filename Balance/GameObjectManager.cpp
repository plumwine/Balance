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
	//�ǉ�����I�u�W�F�N�g���c���Ă�����A�I�u�W�F�N�g���폜�����������J������
	for (auto ptr : m_addObjectList)
	{
		if (ptr != nullptr)
		{
			delete ptr;
		}
	}
	m_addObjectList.clear();

	//�I�u�W�F�N�g��null�ɂȂ����炻�̃��������J������
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


	//�I�u�W�F�N�g�Ǘ�
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


	//�폜
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
		//�I�u�W�F�N�g��null�Ȃ�continue
		if (object == nullptr) continue;


		//�I�u�W�F�N�g�������Ă�����`�悷��
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
//�ǉ�
void GameObjectManager::Add(Object * pObject)
{
	m_addObjectList.emplace_back(pObject);

}

void GameObjectManager::enemyDir()
{
	//�G�ȊO�Ȃ�continue
	for (auto enemies : mObjects)
	{
		int dis = 1000;
		if (enemies == nullptr) continue;
		if (enemies->IsDead()) continue;
		Enemy* ene = dynamic_cast<Enemy*>(enemies);
		//�e�̕���
		for (auto bullets : mObjects)
		{
		    if (bullets == nullptr) continue;
		    if (bullets->IsDead()) continue;
			Bullet* bul = dynamic_cast<Bullet *>(bullets);

		    
		    float dis_2 = bul->Position().x - ene->Position().x + bul->Position().y - ene->Position().y;
		    
		    if (dis >= dis_2)
		    {
		    	dis = dis_2;
		    	//�G�̌��m
		    	bul->AreaHit(*ene);
		    }
		}
	}
}


//��ԏ��Cannon��X���W�̎擾
float GameObjectManager::TopCannon()
{

	int Topnum = 1;
	float Top_X = 900;
	for (auto cannon : mObjects)
	{
		if (cannon == nullptr) continue;
		if (cannon->IsDead()) continue;

		//�^���L���X�g���āAnull�ɂȂ�Ȃ��������̂�top�Ƃ���
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
