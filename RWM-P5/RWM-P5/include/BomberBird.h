#ifndef BOMBERBIRD_H
#define BOMBERBIRD_H

#include "BaseBirdObject.h"
#include "UniqueIDGenerator.h"
#include "BombBird.h"

namespace GameEntities
{
	class BomberBird : public BaseBirdObject
	{
	private:
		std::vector<GameEntities::BombBird*> m_bomblist;     //The object list used to store the bombs.
		std::vector<GameEntities::BombBird*>::iterator m_bombIterator;
		Ogre::SceneManager * m_sceneMgr;
		hkpWorld* m_world;
		GameUtilities::UniqueIDGenerator * m_uniqueIDGenerator;
		hkpRigidBodyCinfo m_bombInfo;
		bool m_isBombDropped;

	public:
		/*!	Constructor.
		 * 
		 *	Creates an instance of the SphereObject, and sets up its varies properties.
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
		BomberBird(Ogre::SceneManager * sceneManager, hkpWorld* world, long objectID, Ogre::Vector3 position,  const hkReal radius,  const hkReal sphereMass, hkpRigidBodyCinfo & info, EntityType type);

		~BomberBird();

		void update(float timeSinceLastFrame);
		void dropBomb();
		bool getIsBombDropped();
	}; // class SphereObject
} // namespace GameEntities

#endif