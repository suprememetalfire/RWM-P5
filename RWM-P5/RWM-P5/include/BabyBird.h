#ifndef BABYBIRD_H
#define BABYBIRD_H

#include "BaseBirdObject.h"

namespace GameEntities
{
	class BabyBird : public BaseBirdObject
	{
	private:

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
		BabyBird(Ogre::SceneManager * sceneManager, hkpWorld* world, long objectID, Ogre::Vector3 position,  const hkReal radius,  const hkReal sphereMass, hkpRigidBodyCinfo & info, EntityType type);

		~BabyBird();

		void update();
	}; // class SphereObject
} // namespace GameEntities

#endif