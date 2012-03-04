#pragma once
#ifndef LEVEL_H
#define LEVEL_H


#include "UniqueIDGenerator.h"
#include "MaterialFactory.h"
#include <time.h>
#include <vector>

using namespace std;

namespace GameUtilities
{
	class Level
	{
	private:
		/*!	Constructor.
		 * 
		 *	Creates an instance of the Level, and sets up its varies properties.
		 */
		Level();
		~Level();
		static Level * m_instance;
		static Ogre::SceneManager * m_sceneMgr;
		static hkpWorld* m_world;
		static GameUtilities::UniqueIDGenerator * m_uniqueIDGenerator;
		static MaterialFactory * m_matFactory;
		hkpRigidBodyCinfo m_boxFixtureDefinition;
		hkpRigidBodyCinfo m_pigFixtureDefinition;
		int m_currentLevel;
	public:
		static Level * getInstance(Ogre::SceneManager * sceneManager = 0, hkpWorld * world = 0);

		void Update(float timeSinceLastFrame);
		void createLevel1();
		void createLevel2();
		void createLevel3();
		bool checkLevelWin();
		void beatLevel();
		void clearLevelObjectData();

		void setCurrentLevel(int newCurrentLevel);
		int getCurrentLevel();

		std::vector<GameEntities::BoxObject*> & getLevelObjectList();
		std::vector<GameEntities::SphereObject*> & getPigList();
	};
}
#endif