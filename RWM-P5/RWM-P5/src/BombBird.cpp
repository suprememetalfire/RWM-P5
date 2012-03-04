#include "BombBird.h"

const int maxEffectiveDistance = 100;
const int explosionForce = 100000;
const int forceScaler = 100000;
namespace GameEntities
{
	BombBird::BombBird(Ogre::SceneManager * sceneManager, hkpWorld* world, long objectID, 
		Ogre::Vector3 position,  const hkReal radius,  
		const hkReal sphereMass, hkpRigidBodyCinfo & info, 
		EntityType type)
		:BaseBirdObject(sceneManager,world,objectID,position,radius,sphereMass,info,type)
	{
		m_level = GameUtilities::Level::getInstance(sceneManager, world);
		m_timeToExplode = 0;
	}

	BombBird::~BombBird()
	{	
	}

	void BombBird::update(float timeSinceLastFrame)
	{
		if(!this->getIsDeleted())
		{
			BaseBirdObject::update();
			m_timeToExplode += timeSinceLastFrame;
			if(m_timeToExplode > 5.0)
			{
				//explode
				explode();
			}
		}
	}

	void BombBird::explode()
	{
		//delete the bird itself
		this->deleteObject();
		//apply fource to all the objects around it
		std::vector<GameEntities::BoxObject*> m_levelObjects;
		std :: vector<GameEntities :: BoxObject*> :: iterator m_levelObjectsIterator;
		std::vector<GameEntities::SphereObject*> m_pigs;
		std :: vector<GameEntities ::SphereObject*> :: iterator m_pigsIterator;
		m_levelObjects = m_level->getLevelObjectList();
		m_pigs = m_level->getPigList();
		if(!m_levelObjects.empty())
		{
			for(m_levelObjectsIterator = m_levelObjects.begin(); m_levelObjectsIterator != m_levelObjects.end(); m_levelObjectsIterator++)
			{
				if(!(*m_levelObjectsIterator)->getIsDeleted())
				{
					//get the distance from the bomb bird and the level objects
					float distance = this->getBody()->getPosition().distanceTo((*m_levelObjectsIterator)->getBody()->getPosition());
					if(distance < maxEffectiveDistance)
					{
						//calculate the force depends on the distance
						float force = explosionForce*((maxEffectiveDistance-distance)/maxEffectiveDistance);
						//calculate the angle of the direction from the bomb bird to the objects
						float angle = atan2f((*m_levelObjectsIterator)->getBody()->getPosition()(1)-this->getBody()->getPosition()(1),(*m_levelObjectsIterator)->getBody()->getPosition()(0)-this->getBody()->getPosition()(0));
						//calculate the direction of the force
						hkVector4 dir;
						dir(0) = forceScaler*cosf(angle*force);
						dir(1) = forceScaler*sinf(angle*force);
						dir(2) = 0;
						//apply the fource onto the object
						(*m_levelObjectsIterator)->getBody()->applyLinearImpulse(dir);
					}
				}
			}
		}
		if(!m_pigs.empty())
		{
			for(m_pigsIterator = m_pigs.begin(); m_pigsIterator != m_pigs.end(); m_pigsIterator++)
			{
				if(!(*m_pigsIterator)->getIsDeleted())
				{
					//get the distance from the bomb bird and the level objects
					float distance = this->getBody()->getPosition().distanceTo((*m_pigsIterator)->getBody()->getPosition());
					if(distance < maxEffectiveDistance)
					{
						//calculate the force depends on the distance
						float force = explosionForce*((maxEffectiveDistance-distance)/maxEffectiveDistance);
						//calculate the angle of the direction from the bomb bird to the objects
						float angle = atan2f((*m_pigsIterator)->getBody()->getPosition()(1)-this->getBody()->getPosition()(1),(*m_pigsIterator)->getBody()->getPosition()(0)-this->getBody()->getPosition()(0));
						//calculate the direction of the force
						hkVector4 dir;
						dir(0) = forceScaler*cosf(angle*force);
						dir(1) = forceScaler*sinf(angle*force);
						dir(2) = 0;
						//apply the fource onto the object
						(*m_pigsIterator)->getBody()->applyLinearImpulse(dir);
					}
				}				
			}
		}
	}

}