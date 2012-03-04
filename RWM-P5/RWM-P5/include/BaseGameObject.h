#ifndef BASEGAMEOBJECT_H
#define BASEGAMEOBJECT_H

#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include "Physics.h"

enum EntityType
{
	MAT_WOOD = 0,
	MAT_ICE = 1,
	MAT_STONE = 2,
	MAT_NORMAL = 3,
	MAT_ANCHOR = 4,
	MAT_PIG = 5,
	MAT_BIRDONE = 6,
	MAT_BIRDTWO = 7,
	MAT_BIRDTHREE = 8,
	MAT_BIRDFOUR = 9,
	MAT_BIRDFIVE = 10,
	MAT_BOMB = 11,
	MAT_BULLET = 12
};

namespace GameEntities
{
	/*!
	 * A simple class representing a game entity. 
	 *
	 * This class acts as a base wrapper for the Box2D and Ogre3D elements.
	 * Other classes can inherit from this class to create more complex objects,
	 * such as the BoxObject class.
	 */
	class BaseGameObject
	{
	protected:
		Ogre::SceneNode * m_sceneNode;						//!< SceneNode holding the Ogre-side data.
		Ogre::Entity * m_entity;							//!< Ogre Entity that can be seen on-screen.
		hkpRigidBody * m_body;								//!< Havok body holding the Havok-side data.
		long m_ID;											//!< A unique ID for each instance of this class.
		bool m_contacting;									//!< bool set to true if collision callback function returns true.
		int m_numContacts;									//!< counter that keeps track of the number of collisions at any one time.
		int m_previousNumContacts;							//!< keeps track of the previous number of collisions.
		hkVector4 m_momentum;									//!< The momentum of the game object
		hkVector4 m_lastMomentum;								//!< The last momentum of the game object
		bool isDamaged;										//!< If the object is damaged.
		bool isBroken;										//!< If the object is broken.
		bool isDeleted;										//!< If the object is deleted.
		EntityType mType;									//!< The type of this object
		hkpWorld *m_world;									//!< The pointer to the physics world
		Ogre::Vector3 m_deadPos;                            //!< 

		/*! Constructor.
		 * 
		 * @param objectID The unique ID for this instance.
		 */
		BaseGameObject(long & objectID, EntityType objectType, hkpWorld *world) : m_ID(objectID),mType(objectType),m_world(world)
		{ 
			m_contacting = false; 
			m_numContacts = 0;
			m_previousNumContacts = 0;
			isDamaged = false;
			isBroken = false;
			m_momentum = hkVector4( 0.0, 0.0, 0.0 );
			mContacting = false;
			m_lastMomentum = hkVector4(0.0 , 0.0, 0.0);
			isDeleted = false;
			m_deadPos = Ogre::Vector3::ZERO;
			//mType = (EntityType)ObjectIdType;
		}

		//! Destructor.
		~BaseGameObject(){}

	public:
		bool mContacting;
		/*! 
		 *	Returns m_sceneNode.
		 *
		 *	@return SceneNode.
		 */
		Ogre::SceneNode * getSceneNode()
		{
			return m_sceneNode;
		}

		/*! 
		 *	Returns m_entity.
		 *
		 *	@return Entity.
		 */
		Ogre::Entity * getEntity()
		{
			return m_entity;
		}

		/*! 
		 *	Returns m_body.
		 *
		 *	@return Entity.
		 */
		hkpRigidBody * getBody()
		{
			return m_body;
		}

		int NumContacts()
		{
			return m_numContacts;
		}

		/*! Updates the object.
		 * 
		 *	The base update() function simply sets the position and orientation 
		 *	of the Ogre SceneNode to that of the Box2D body.
		 */
		virtual void update()
		{
			if(!isDeleted)
			{
				//check the momentum of this object, should be removed after the collision callback is implemented
				m_momentum = checkMomentum();

				//Update the position of this object
				hkVector4 position = m_body->getPosition();
				m_sceneNode->setPosition(position(0), position(1), position(2));
				//Update the rotation of this object
				hkQuaternion rotQuaternion = m_body->getRotation();
				Ogre::Radian angleRot(rotQuaternion.getAngle());
				hkVector4 axis(0,0,0);
				if(rotQuaternion.hasValidAxis())
					rotQuaternion.getAxis(axis); //get axis of rotaion from quaternion 

				Ogre::Vector3 axisRot(axis(0),axis(1),axis(2));
				Ogre::Quaternion newOgRot(angleRot,axisRot);

				m_sceneNode->setOrientation(newOgRot);

				if(m_lastMomentum(0) <5 && m_momentum(0) > 30 )
				{
					if(mType == MAT_STONE || mType == MAT_ICE || mType == MAT_WOOD || mType == MAT_PIG)
					{
						isDamaged = true;
						if(mType==MAT_ICE)
							changeTexture("CrackedIce");
						else if(mType==MAT_WOOD)
							changeTexture("CrackedWood");
						else if(mType==MAT_STONE)
							changeTexture("CrackedStone");
						else if(mType==MAT_PIG)
							changeTexture("CrackedIce");
					}
				}
				if(m_lastMomentum(1) > 40 && m_momentum(1) <5)
				{
					if(mType == MAT_STONE || mType == MAT_ICE || mType == MAT_WOOD || mType == MAT_PIG)
					{
						isDamaged = true;
						if(mType==MAT_ICE)
							changeTexture("CrackedIce");
						else if(mType==MAT_WOOD)
							changeTexture("CrackedWood");
						else if(mType==MAT_STONE)
							changeTexture("CrackedStone");
						else if(mType==MAT_PIG)
							changeTexture("CrackedIce");
					}
					if(m_lastMomentum(1)>60)
					{
						if(!isDeleted && mType == MAT_STONE || mType == MAT_ICE || mType == MAT_WOOD || mType == MAT_PIG)
						{
							this->deleteObject();
						}
					}
				}
				
				if(m_momentum(0)>100)
				{
					if(!isDeleted && mType == MAT_STONE || mType == MAT_ICE || mType == MAT_WOOD)
					{
						this->deleteObject();
					}
				}
				if(m_momentum(1)>100)
				{
					if(!isDeleted && mType == MAT_PIG)
					{
						this->deleteObject();
					}
				}

				//delete the object if it goes out of the physics world
				if(m_body->getPosition()(0) > 480 || m_body->getPosition()(0)<-480 ||
					m_body->getPosition()(2)>480 || m_body->getPosition()(2)<-480)
				{
					deleteObject();
				}
				//update the momentum
				m_lastMomentum = m_momentum;
			}
		}
		/*! Updates the object.
		 * 
		 *	The base update() function simply sets the position and orientation 
		 *	of the Ogre SceneNode to that of the Box2D body.
		 */
		virtual void updateReverse()
		{
			hkVector4 position;
			position(0) = m_sceneNode->getPosition().x;
			position(1) = m_sceneNode->getPosition().y;
			position(2) = m_sceneNode->getPosition().z;
			m_body->setPosition(position);
		}

		//new implementation for contact state change
	    virtual void startContact() 
		{ 
			m_previousNumContacts = m_numContacts;
			m_numContacts++;

			mContacting = true;
		}

	    virtual void endContact() 
		{ 
			m_previousNumContacts = m_numContacts;
			m_numContacts--;

			mContacting = false;
		}

		hkVector4 checkMomentum()
		{			
			m_momentum(0) = Ogre :: Math :: Abs( m_body->getLinearVelocity()(0)* m_body->getMass()/1000 );
			m_momentum(1) = Ogre :: Math :: Abs( m_body->getLinearVelocity()(1) * m_body->getMass()/1000 );
			m_momentum(2) = Ogre :: Math :: Abs( m_body->getLinearVelocity()(2) * m_body->getMass()/1000 );
			return  m_momentum;
		}

		void changeTexture(Ogre::String name)
		{
			m_entity->setMaterialName(name);
		}

		bool getIsDamaged()
		{
			return isDamaged;
		}
		bool getIsBroken()
		{
			return isBroken;
		}
		bool getIsDeleted()
		{
			return isDeleted;
		}
		void setIsDamaged(bool check)
		{
			isDamaged = check;
		}
		void setIsBroken(bool check)
		{
			isBroken = check;
		}
		void setIsDeleted(bool check)
		{
			isDeleted = check;
		}
		EntityType getMyType()
		{
			return mType;
		}
		Ogre::Vector3 getDeadPos()
		{
			return m_deadPos;
		}
		void deleteObject()
		{
			m_deadPos.x = m_body->getPosition()(0);
			m_deadPos.y = m_body->getPosition()(1);
			m_deadPos.z = m_body->getPosition()(2);
			m_world->removeEntity(m_body);
			m_sceneNode->detachAllObjects();
			isDeleted = true;
		}
	};
}
#endif