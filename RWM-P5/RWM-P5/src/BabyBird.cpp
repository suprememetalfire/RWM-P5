#include "BabyBird.h"

namespace GameEntities
{
	BabyBird::BabyBird(Ogre::SceneManager * sceneManager, hkpWorld* world, long objectID, Ogre::Vector3 position,  const hkReal radius,  const hkReal sphereMass, hkpRigidBodyCinfo & info, EntityType type)
		:BaseBirdObject(sceneManager,world,objectID,position,radius,sphereMass,info,type)
	{
		hkVector4 vel(500.0f,-30.0f, 0.0f );
		this->getBody()->setLinearVelocity( vel );
		hkVector4 angvel(-0.9f,0.0f, 0.0f,1.0 );
		this->getBody()->setAngularVelocity(angvel);
	}

	BabyBird::~BabyBird()

	{}

	void BabyBird::update()
	{
		BaseBirdObject::update();
	}
}