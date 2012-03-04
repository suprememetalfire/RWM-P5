#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include "BoxObject.h"
#include "SphereObject.h"
#include "UniqueIDGenerator.h"

// Forward Declarations
namespace GameEntities
{
	class BoxObject;
	class SphereObject;
	class BaseGameObject;
}

namespace GameUtilities
{
class MaterialFactory
{
	private:
	//The list and the iterator for all the stone/ice/wood objects
	std::vector<GameEntities::BoxObject*> m_levelObjects;
	std::vector<GameEntities::BoxObject*> m_levelObjectParts;
	std::vector<GameEntities::BoxObject*>::iterator m_iterator;
	//The list and the iterator for all the pigs
	std::vector<GameEntities::SphereObject*> m_pigs;
	std::vector<GameEntities::SphereObject*>::iterator m_pigIterator;

	Ogre::SceneManager * m_sceneMgr;
	hkpWorld* m_world;

	GameUtilities::UniqueIDGenerator * m_uniqueIDGenerator;

	hkpRigidBodyCinfo partsInfo;
	public:
		/*!	Constructor.
		 * 
		 *	Creates an instance of the MaterialFactory, and sets up its varies properties.
		 */
		MaterialFactory(Ogre::SceneManager * sceneMgr, hkpWorld* world) : m_sceneMgr(sceneMgr), m_world(world)
		{
			m_uniqueIDGenerator = GameUtilities::UniqueIDGenerator::getInstance();
		}

		~MaterialFactory(void)
		{
			//clear the level object list
			for(size_t i = 0; i < m_levelObjects.size(); ++i)
			{
				delete m_levelObjects[i];
			}
			m_levelObjects.clear();
			//clear the pig list
			for(size_t i = 0; i < m_pigs.size(); ++i)
			{
				delete m_pigs[i];
			}
			m_pigs.clear();
		}
		//Object creation method for the stone/ice/wood objects
		void CreateObject(long objectID, Ogre::Vector3 position, float size,Ogre::String materialName, EntityType type, hkpRigidBodyCinfo & info)
		{
			switch(type)
			{
				case MAT_WOOD:
					m_levelObjects.push_back(new GameEntities::BoxObject(m_sceneMgr, m_world, objectID, position, size, materialName, type, info));
					break;
				case MAT_ICE:
					m_levelObjects.push_back(new GameEntities::BoxObject(m_sceneMgr, m_world, objectID, position, size, materialName, type, info));
					break;
				case MAT_STONE:
					m_levelObjects.push_back(new GameEntities::BoxObject(m_sceneMgr, m_world, objectID, position, size, materialName, type, info));
					break;
			}
		}
		//Object creation method for the pigs
		void CreateObject(long objectID, Ogre::Vector3 position, const hkReal radius, const hkReal mass,hkpRigidBodyCinfo & info, EntityType type)
		{
			if(type == MAT_PIG)
			{
				m_pigs.push_back(new GameEntities::SphereObject(m_sceneMgr, m_world, objectID, position, radius, mass, info, type));
			}
		}

		void Update()
		{
			Ogre::String matName;
			if(!m_levelObjects.empty())
			{
				for(m_iterator = m_levelObjects.begin(); m_iterator!= m_levelObjects.end(); ++m_iterator)
				{
					if(!(*m_iterator)->getIsDeleted())
					{
						(*m_iterator)->update();
					}
					else
					{
						if(!(*m_iterator)->getIsBroken())
						{
							switch((*m_iterator)->getMyType())
							{
								case MAT_WOOD:
									matName = "WoodPallet";
									break;
								case MAT_ICE:
									matName = "Examples/WaterStream";
									break;
								case MAT_STONE:
									matName = "Examples/Rocky";
									break;
							}
							m_levelObjectParts.push_back(new GameEntities::BoxObject(m_sceneMgr, m_world, m_uniqueIDGenerator->getNewID(),(*m_iterator)->getDeadPos(), (*m_iterator)->getSize()/3, matName , MAT_NORMAL, partsInfo));
							m_levelObjectParts.push_back(new GameEntities::BoxObject(m_sceneMgr, m_world, m_uniqueIDGenerator->getNewID(),(*m_iterator)->getDeadPos(), (*m_iterator)->getSize()/3, matName , MAT_NORMAL, partsInfo));
							m_levelObjectParts.push_back(new GameEntities::BoxObject(m_sceneMgr, m_world, m_uniqueIDGenerator->getNewID(),(*m_iterator)->getDeadPos(), (*m_iterator)->getSize()/3, matName , MAT_NORMAL, partsInfo));
							(*m_iterator)->setIsBroken(true);
						}
					}
				}
			}
			if(!m_pigs.empty())
			{
				for(m_pigIterator = m_pigs.begin(); m_pigIterator!= m_pigs.end(); ++m_pigIterator)
				{
					(*m_pigIterator)->update();
				}
			}
			if(!m_levelObjectParts.empty())
			{
				for(m_iterator = m_levelObjectParts.begin(); m_iterator!= m_levelObjectParts.end(); ++m_iterator)
				{
					(*m_iterator)->update();
				}			
			}
		}

		std::vector<GameEntities::BoxObject*> & getLevelObjectList()
		{
			return m_levelObjects;
		}

		std::vector<GameEntities::SphereObject*> & getPigList()
		{
			return m_pigs;
		}
	};
}

#endif