#ifndef BOXOBJECT_H
#define BOXOBJECT_H

#include "BaseGameObject.h"
namespace GameEntities
{
	class BoxObject : public BaseGameObject
	{
	private:
		float m_size;
	public:
		/*!	Constructor.
		 * 
		 *	Creates an instance of the BoxObject, and sets up its varies properties.
		 *
		 * @param sceneManager A pointer to the SceneManager, used for creating Ogre
		 * Entities and SceneNodes.
		 * @param world The Box2D World object, used for creating bodies and fixtures.
		 * @param objectID The unique ID for this instance.
		 * @param position Initial position for this object.
		 * @param halfWidth Half the desired width of the box.
		 * @param halfHeight Half the desired height of the box.
		 * @param materialName the material name of the box.
		 * @param fixtureDefinition Fixture definition describing the properties of the
		 * box.
		 */
		BoxObject(Ogre::SceneManager * sceneManager, hkpWorld* world, long objectID, Ogre::Vector3 position, float size, Ogre::String materialName, EntityType type, hkpRigidBodyCinfo & info);

		~BoxObject();

		float getSize();
	}; // class BoxObject
} // namespace GameEntities

#endif