#ifndef BASEBIRDOBJECT_H
#define BASEBIRDOBJECT_H

#include "BaseGameObject.h"

namespace GameEntities
{
	class BaseBirdObject : public BaseGameObject
	{
	protected:
		bool isAttached;
		/*!	Constructor.
		 * 
		 *	Creates an instance of the BaseBirdObject, and sets up its varies properties.
		 *
		 * @param sceneManager A pointer to the SceneManager, used for creating Ogre
		 * Entities and SceneNodes.
		 * @param world The Box2D World object, used for creating bodies and fixtures.
		 * @param objectID The unique ID for this instance.
		 * @param position Initial position for this object.
		 * @param radius Half the desired width of the sphere.
		 * @param halfHeight Half the desired height of the sphere.
		 * @param fixtureDefinition Fixture definition describing the properties of the
		 * sphere.
		 */
		BaseBirdObject(Ogre::SceneManager * sceneManager, hkpWorld* world, long objectID, Ogre::Vector3 position,  const hkReal radius,  const hkReal sphereMass, hkpRigidBodyCinfo & info, EntityType type): BaseGameObject(objectID,type,world)
		{
			char entName[16];
			char nodeName[16];
			switch(type)
			{
			case MAT_BIRDONE:
				{
					sprintf(entName, "BirdOne%d", objectID);
					m_entity = sceneManager->createEntity(entName, "bomberbird.mesh");
					sprintf(nodeName, "BirdOne%d", objectID);
					m_sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(nodeName, position);				
				}
				break;
			case MAT_BIRDTWO:
				{
					sprintf(entName, "BirdTwo%d", objectID);
					m_entity = sceneManager->createEntity(entName, "ogrehead.mesh");
					sprintf(nodeName, "BirdTwo%d", objectID);
					m_sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(nodeName, position);				
				}
				break;
			case MAT_BIRDTHREE:
				{
					sprintf(entName, "BirdThree%d", objectID);
					m_entity = sceneManager->createEntity(entName, "mombird.mesh");
					sprintf(nodeName, "BirdThree%d", objectID);
					m_sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(nodeName, position);				
				}
				break;
			case MAT_BIRDFOUR:
				{
					sprintf(entName, "BirdFour%d", objectID);
					m_entity = sceneManager->createEntity(entName, "assaultbird.mesh");
					sprintf(nodeName, "BirdFour%d", objectID);
					m_sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(nodeName, position);				
				}
				break;
			case MAT_BIRDFIVE:
				{
					sprintf(entName, "BirdFive%d", objectID);
					m_entity = sceneManager->createEntity(entName, "babybird.mesh");
					sprintf(nodeName, "BirdFive%d", objectID);
					m_sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode(nodeName, position);		
				}
				break;
			case MAT_BOMB:
				{
					sprintf(entName, "BombBird%d", objectID);
					m_entity = sceneManager->createEntity(entName, "bomberbird.mesh");
					sprintf(nodeName, "BombBird%d", objectID);
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

			isAttached = false;
		}

		~BaseBirdObject(){};

	public:
		virtual void update()
		{
			BaseGameObject::update();
		}
		bool getIsAttached()
		{
			return isAttached;
		}
		void setIsAttached(bool attached)
		{
			isAttached = attached;
		}
	}; // class SphereObject
} // namespace GameEntities

#endif