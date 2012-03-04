#ifndef BOMBBIRD_H
#define BOMBBIRD_H

#include "BaseBirdObject.h"
#include "Level.h"

namespace GameEntities
{
	class BombBird : public BaseBirdObject
	{
	private:
		float m_timeToExplode;
		GameUtilities::Level* m_level;
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
		BombBird(Ogre::SceneManager * sceneManager, hkpWorld* world, long objectID, 
			Ogre::Vector3 position,  const hkReal radius,  const hkReal sphereMass, 
			hkpRigidBodyCinfo & info, EntityType type);

		~BombBird();

		void update(float timeSinceLastFrame);
		void explode();
	}; // class SphereObject
} // namespace GameEntities

#endif