#include "SphereObject.h"

namespace GameEntities
{
	SphereObject::SphereObject(Ogre::SceneManager * sceneManager, hkpWorld* world, long objectID, Ogre::Vector3 position, const hkReal radius, const hkReal sphereMass, hkpRigidBodyCinfo & info,EntityType type) : BaseGameObject(objectID,type,world)
	{
		char entName[16];
		char nodeName[16];
		switch(type)
		{
		case MAT_BOMB:
			{
				sprintf(entName, "BirdOne%d", objectID);
				m_entity = sceneManager->createEntity(entName, "bomberbird.mesh");
				sprintf(nodeName, "BirdOne%d", objectID);
				m_sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(nodeName, position);				
			}
			break;
		case MAT_PIG:
			{
				sprintf(entName, "Pig%d", objectID);
				m_entity = sceneManager->createEntity(entName, "penguin.mesh");
				sprintf(nodeName, "Pig%d", objectID);
				m_sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(nodeName, position);
			}
			break;
		case MAT_BULLET:
			{
				sprintf(entName, "Bullet%d", objectID);
				m_entity = sceneManager->createEntity(entName, "sphere.mesh");
				sprintf(nodeName, "Bullet%d", objectID);
				m_sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(nodeName, position);
			}
			break;
		}
		//change the material 
		//m_entity->setMaterialName(materialName);
		// Create box scene node and attach the box entity.
		m_sceneNode->attachObject(m_entity);

		float r = m_entity->getBoundingRadius();
		float scalefactor = 1.5*radius/r; //scale by desired radius, divide by actual radius
		m_sceneNode->setScale(scalefactor,scalefactor,scalefactor);

		//set up physics properties of havok object
		hkpMassProperties massProperties;
		hkpInertiaTensorComputer::computeSphereVolumeMassProperties(
			radius, sphereMass, massProperties);

		info.m_mass = massProperties.m_mass;
		info.m_centerOfMass  = massProperties.m_centerOfMass;
		info.m_inertiaTensor = massProperties.m_inertiaTensor;
		info.m_shape = new hkpSphereShape( radius );
		info.m_position(0) = position.x;
		info.m_position(1) = position.y;
		info.m_position(2) = position.z;
		info.m_motionType  = hkpMotion::MOTION_SPHERE_INERTIA;
		info.m_qualityType = HK_COLLIDABLE_QUALITY_BULLET;//for fast objects

		m_body = new hkpRigidBody( info );
	
		info.m_shape->removeReference();

		world->addEntity(m_body);
	}
} // namespace GameEntities