#include "AssaultBird.h"

namespace GameEntities
{
	AssaultBird::AssaultBird(Ogre::SceneManager * sceneManager, hkpWorld* world, long objectID, Ogre::Vector3 position,  const hkReal radius,  const hkReal sphereMass, hkpRigidBodyCinfo & info, EntityType type)
		:BaseBirdObject(sceneManager,world,objectID,position,radius,sphereMass,info,type)
	{
		m_sceneMgr = sceneManager;
		m_world = world;

		m_uniqueIDGenerator = GameUtilities::UniqueIDGenerator::getInstance();
		m_bulletInfo.m_friction = 0.7;
		m_bulletInfo.m_restitution = 0.0;

		index = 0;
	}

	AssaultBird::~AssaultBird()
	{}

	void AssaultBird::update()
	{
		BaseBirdObject::update();

		if(!m_bulletList.empty())
		{
			for(m_bulletIterator = m_bulletList.begin(); m_bulletIterator!= m_bulletList.end(); ++m_bulletIterator)
			{
				(*m_bulletIterator)->update();
			}
		}
	}

	void AssaultBird::shoot()
	{
		if(m_bulletList.size() < 3)
		{
			m_bulletList.push_back(new GameEntities::SphereObject(m_sceneMgr, m_world, m_uniqueIDGenerator->getNewID(), 
				Ogre::Vector3(m_body->getPosition()(0), m_body->getPosition()(1), m_body->getPosition()(2)), 1, 300, m_bulletInfo, MAT_BULLET));
			
			hkVector4 vel(500.0f,-30.0f, 0.0f);
			m_bulletList.at(index)->getBody()->setLinearVelocity(vel);;
			hkVector4 angvel(-0.9f ,0.0f, 0.0f, 1.0);
			m_bulletList.at(index)->getBody()->setAngularVelocity(angvel);
			
			index++;
		}
	}
}