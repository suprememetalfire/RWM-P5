#ifndef ASSAULTBIRD_H
#define ASSAULTBIRD_H

#include "BaseBirdObject.h"
#include "SphereObject.h"
#include "UniqueIDGenerator.h"

namespace GameEntities
{
	class AssaultBird : public BaseBirdObject 
	{
		private:
		std::vector<GameEntities::SphereObject*> m_bulletList;     // Object list used to store the bullets.
		std::vector<GameEntities::SphereObject*>::iterator m_bulletIterator;
		Ogre::SceneManager * m_sceneMgr;
		hkpWorld* m_world;
		GameUtilities::UniqueIDGenerator * m_uniqueIDGenerator;
		hkpRigidBodyCinfo m_bulletInfo;
		int index;

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
		AssaultBird(Ogre::SceneManager * sceneManager, hkpWorld* world, long objectID, Ogre::Vector3 position,  const hkReal radius,  const hkReal sphereMass, hkpRigidBodyCinfo & info, EntityType type);

		~AssaultBird();

		void update();
		void shoot();
	};
}

#endif