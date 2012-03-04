#include "MomBird.h"

namespace GameEntities
{
	MomBird::MomBird(Ogre::SceneManager * sceneManager, hkpWorld* world, long objectID, Ogre::Vector3 position,  const hkReal radius,  const hkReal sphereMass, hkpRigidBodyCinfo & info, EntityType type)
		:BaseBirdObject(sceneManager,world,objectID,position,radius,sphereMass,info,type)
	{
		abilityUsed = false;
		sceneMan = sceneManager;
		havokWorld = world;
		sphereInfo = info;
		m_uniqueIDGenerator = GameUtilities::UniqueIDGenerator::getInstance();
	}

	MomBird::~MomBird()
	{

	}

	void MomBird::useAbility()
	{
		if (abilityUsed == false)
		{
			Ogre::Vector3 momPos;
			momPos.x = this->getBody()->getPosition().getComponent(0);
			momPos.y = this->getBody()->getPosition().getComponent(1);
			momPos.z = this->getBody()->getPosition().getComponent(2);
			//the current code breaks the game, use the UniqueIDgenerator instead of 5+i
			for	(int i = 0; i < 50; i++)
			{
				m_babyBird[i] = new BabyBird(sceneMan, havokWorld,m_uniqueIDGenerator->getNewID(), momPos, 1.5, 100, sphereInfo, MAT_BIRDFIVE);
			}
			this->deleteObject();
		}
		abilityUsed = true;
	}

	void MomBird::update()
	{		
		if (abilityUsed)
		{
			for	(int i = 0; i < 50; i++)
			{
				if(!m_babyBird[i]->getIsDeleted())
				{
					m_babyBird[i]->update();
				}
			}
		}
		else
		{
			BaseBirdObject::update();
		}
	}

	void MomBird::deleteAllBabyBirds()
	{
		for	(int i = 0; i < 50; i++)
		{
			if(!m_babyBird[i]->getIsDeleted())
			{
				m_babyBird[i]->deleteObject();
				delete m_babyBird[i];
			}
		}
	}
}