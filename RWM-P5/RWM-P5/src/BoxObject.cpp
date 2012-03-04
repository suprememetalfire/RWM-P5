#include "BoxObject.h"

namespace GameEntities
{
	BoxObject::BoxObject(Ogre::SceneManager * sceneManager, hkpWorld* world, long objectID, Ogre::Vector3 position, float size, Ogre::String materialName, EntityType type, hkpRigidBodyCinfo & info) : BaseGameObject(objectID,type,world)
	{
		char entName[16];
		char nodeName[16];
		// Create box entity and set its material.
		switch(type)
		{
		case MAT_WOOD:
			{	
				sprintf(entName, "WoodEntity%d", objectID);
				m_entity = sceneManager->createEntity(entName, "cube.mesh");
				sprintf(nodeName, "WoodNode%d", objectID);
				m_sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(nodeName, position);
				info.m_mass = 6000;
			}
			break;
		case MAT_ICE:
			{
				sprintf(entName, "IceEntity%d", objectID);
				m_entity = sceneManager->createEntity(entName, "cube.mesh");
				sprintf(nodeName, "IceNode%d", objectID);
				m_sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(nodeName, position);
				info.m_mass = 8000;
			}
			break;
		case MAT_STONE:
			{
				sprintf(entName, "StoneEntity%d", objectID);
				m_entity = sceneManager->createEntity(entName, "cube.mesh");
				sprintf(nodeName, "StoneNode%d", objectID);
				m_sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(nodeName, position);
				info.m_mass = 9000;
			}
			break;
		case MAT_NORMAL:
			{
				sprintf(entName, "NormalEntity%d", objectID);
				m_entity = sceneManager->createEntity(entName, "cube.mesh");
				sprintf(nodeName, "NormalNode%d", objectID);
				m_sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(nodeName, position);
				info.m_mass = 200;
			}
			break;
		case MAT_ANCHOR:
			{
				sprintf(entName, "AnchorEntity%d", objectID);
				m_entity = sceneManager->createEntity(entName, "athene.mesh");
				sprintf(nodeName, "AnchorNode%d", objectID);
				m_sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(nodeName, position);
				info.m_mass = 50;
			}
			break;
		}
		//store the type
		mType=type;
		//change the material 
		m_entity->setMaterialName(materialName);
		// Create box scene node and attach the box entity.
		m_sceneNode->attachObject(m_entity);

		// Scale the Ogre box mesh down to size, as it starts off at 100m x 100m x 100m.
		m_size = size;
		Ogre::AxisAlignedBox abb = m_entity->getBoundingBox();
		Ogre::Vector3 sz = abb.getSize();
		float scalesize=size/sz.x;
		m_sceneNode->setScale(scalesize,scalesize,scalesize);

		//set up physics properties of havok object
		hkVector4 boxHalfSize( size/2.0,size/2.0,size/2.0);
		hkpBoxShape* hbox = new hkpBoxShape( boxHalfSize , 0 );
		hbox->setRadius( 0.0f );

		if(mType != MAT_ANCHOR)
		{
			//create a box like rigid body
			hkpMassProperties massProperties;
			hkpInertiaTensorComputer::computeBoxVolumeMassProperties(
				boxHalfSize, info.m_mass, massProperties);

			info.m_mass = massProperties.m_mass;
			info.m_centerOfMass = massProperties.m_centerOfMass;
			info.m_inertiaTensor = massProperties.m_inertiaTensor;
			info.m_solverDeactivation = info.SOLVER_DEACTIVATION_MEDIUM; // used to deal with resting contacts
			info.m_shape = hbox;
			info.m_qualityType = HK_COLLIDABLE_QUALITY_MOVING;// default collision quality
			info.m_motionType = hkpMotion::MOTION_BOX_INERTIA;
		}
		else
		{
			info.m_shape = hbox;
			//info.m_collisionFilterInfo=-1;
			info.m_motionType = hkpMotion::MOTION_FIXED;
		}

		info.m_position(0) = position.x;
		info.m_position(1) = position.y;
		info.m_position(2) = position.z;

		m_body = new hkpRigidBody(info);

		//info.m_shape->removeReference();

		world->addEntity(m_body);
	}

	float BoxObject::getSize()
	{
		return m_size;
	}
} // namespace GameEntities