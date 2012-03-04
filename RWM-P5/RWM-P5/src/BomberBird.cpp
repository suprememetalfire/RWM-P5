#include "BomberBird.h"

namespace GameEntities
{
	BomberBird::BomberBird(Ogre::SceneManager * sceneManager, hkpWorld* world, long objectID, Ogre::Vector3 position,  const hkReal radius,  const hkReal sphereMass, hkpRigidBodyCinfo & info, EntityType type)
		:BaseBirdObject(sceneManager,world,objectID,position,radius,sphereMass,info,type)
	{
		m_sceneMgr = sceneManager;
		m_world = world;
		// Instantiate the unique ID generator used when creating game entities.
		m_uniqueIDGenerator = GameUtilities::UniqueIDGenerator::getInstance();
		m_bombInfo.m_friction = 0.9;
		m_bombInfo.m_restitution = 0.0;
		m_isBombDropped = false;
	}

	BomberBird::~BomberBird()
	{
	}

	void BomberBird::update(float timeSinceLastFrame)
	{
		BaseBirdObject::update();
		if(!m_bomblist.empty())
		{
			for(m_bombIterator = m_bomblist.begin(); m_bombIterator!= m_bomblist.end(); ++m_bombIterator)
			{
				(*m_bombIterator)->update(timeSinceLastFrame);
			}
		}

	}
	void BomberBird::dropBomb()
	{
		if(m_bomblist.size()<3)
		{
			m_bomblist.push_back(new GameEntities::BombBird(m_sceneMgr, m_world, m_uniqueIDGenerator->getNewID(), Ogre::Vector3(m_body->getPosition()(0),m_body->getPosition()(1),m_body->getPosition()(2)), 3, 2000, m_bombInfo, MAT_BOMB));
		}
		m_isBombDropped = true;
	}

	bool BomberBird::getIsBombDropped()
	{
		return m_isBombDropped;
	}
}