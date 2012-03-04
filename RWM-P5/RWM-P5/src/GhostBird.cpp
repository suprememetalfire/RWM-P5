#include "GhostBird.h"

namespace GameEntities
{
	GhostBird :: GhostBird( Ogre :: SceneManager * sceneManager, hkpWorld* world, long objectID, Ogre :: Vector3 position, const hkReal radius, const hkReal sphereMass, 
		                    hkpRigidBodyCinfo & info, EntityType type, hkpPairCollisionFilter* filter, std::vector<GameEntities::BoxObject*> & levellist)
																		: BaseBirdObject( sceneManager, world, objectID, position, radius, sphereMass, info, type )
	{
		m_filter = filter;
		m_levelObjects = levellist;
	}

	GhostBird :: ~GhostBird()
	{
	}

	void GhostBird :: update()
	{
		BaseBirdObject :: update();
	}

	/**
	 * This function disables the collisions detection between the bird and two of the materials, 
	 * so that the bird will pass through them and collide with the last material.
	 *
	 * @param ability The material that the bird will collide with.
	 */
	void GhostBird :: useAbility( int ability )
	{
		std :: vector<GameEntities :: BoxObject*> :: iterator m_filterIterator;

		if( !m_levelObjects.empty() )
		{
			for( m_filterIterator = m_levelObjects.begin(); m_filterIterator != m_levelObjects.end(); ++m_filterIterator )
			{
				switch( ability )
				{
				case 1:
						// Will only hit ice blocks //					
						this->getEntity()->setMaterialName( "Examples/WaterStream" );

						if( ( *m_filterIterator )->getMyType() != MAT_ICE )
						{
							m_filter->disableCollisionsBetween( ( *m_filterIterator )->getBody(), m_body );
						}				
						break;
					case 2:
						// Will only hit stone blocks //
						this->getEntity()->setMaterialName( "Examples/Rocky" );

						if( ( *m_filterIterator )->getMyType() != MAT_STONE )
						{
							m_filter->disableCollisionsBetween( ( *m_filterIterator )->getBody(), m_body );
						}			
						break;
					case 3:
						// Will only hit wood blocks //
						this->getEntity()->setMaterialName( "WoodPallet" );

						if( ( *m_filterIterator )->getMyType() != MAT_WOOD )
						{
							m_filter->disableCollisionsBetween( (*m_filterIterator)->getBody(), m_body );
						}
						break;
				}
			}
		}
	}
}