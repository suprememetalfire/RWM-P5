#ifndef GHOSTBIRD_H
#define GHOSTBIRD_H

#include "BaseBirdObject.h"
#include <Physics/Dynamics/Collide/Filter/Pair/hkpPairCollisionFilter.h>
#include "BoxObject.h"

namespace GameEntities
{
	class GhostBird : public BaseBirdObject
	{
	private:
		std::vector<GameEntities::BoxObject*> m_levelObjects;
		hkpPairCollisionFilter* m_filter;
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

		GhostBird( Ogre :: SceneManager * sceneManager, hkpWorld* world, long objectID, Ogre :: Vector3 position,  const hkReal radius,  const hkReal sphereMass, 
				   hkpRigidBodyCinfo & info, EntityType type, hkpPairCollisionFilter* filter, std::vector<GameEntities::BoxObject*> & levellist );

		~GhostBird();

		void update();
		void useAbility( int ability );
	}; // class SphereObject
} // namespace GameEntities

#endif