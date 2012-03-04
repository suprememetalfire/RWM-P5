#include "Level.h"

namespace GameUtilities
{
	Level * Level::m_instance = 0;
	Ogre::SceneManager * Level::m_sceneMgr = 0;
	GameUtilities::UniqueIDGenerator * Level::m_uniqueIDGenerator = 0;
	hkpWorld * Level::m_world = 0;
	MaterialFactory * Level::m_matFactory = 0;

	
	Level::Level()
	{

		srand( NULL );
	}

	Level::~Level()
	{

	}

	Level * Level::getInstance(Ogre::SceneManager * sceneManager, hkpWorld * world)
	{
		if(!m_instance)
		{
			m_instance = new Level();

			if(sceneManager != 0 && world != 0)
			{
				m_sceneMgr = sceneManager;
				m_world = world;

				m_matFactory = new MaterialFactory(m_sceneMgr, m_world);

				// Instantiate the unique ID generator used when creating game entities.
				m_uniqueIDGenerator = GameUtilities::UniqueIDGenerator::getInstance();

			}
		}
	
		return m_instance;
	}

	void Level::Update(float timeSinceLastFrame)
	{
		m_matFactory->Update();

		/*if (checkLevelWin())
		{
			beatLevel();
		}*/
	}


	void Level::createLevel1()
	{
		m_currentLevel =1;
		//set the fixture definition for the ice object
		m_boxFixtureDefinition.m_friction = 0.2;
		m_boxFixtureDefinition.m_restitution = 0.2;

		//set the fixture definition for the stone object
		m_boxFixtureDefinition.m_friction = 0.9;
		m_boxFixtureDefinition.m_restitution = 0.0;

		//set the fixture definition for the wood object
		m_boxFixtureDefinition.m_friction = 0.7;
		m_boxFixtureDefinition.m_restitution = 0.2;

		//create all the ice object in the level
		//m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,15,0),10,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
		for (int i = 0; i < 2; i++)
		{
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-20,47 + i*10,-20),10,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-20,47 + i*10,-10),10,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-20,47 + i*10,0),10,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-20,47 + i*10,10),10,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-20,47 + i*10,20),10,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);

			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-10,47 + i*10,20),10,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,47 + i*10,20),10,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(10,47 + i*10,20),10,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(20,47 + i*10,20),10,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
			
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-10,47 + i*10,-20),10,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,47 + i*10,-20),10,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(10,47 + i*10,-20),10,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(20,47 + i*10,-20),10,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);

			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(20,47 + i*10,-10),10,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(20,47 + i*10,0),10,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(20,47 + i*10,10),10,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
		
		//create all the stone object in the level
		
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-20,7 + i*10,-20),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-20,7 + i*10,-10),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-20,7 + i*10,0),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-20,7 + i*10,10),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-20,7 + i*10,20),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);

			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-10,7 + i*10,20),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,7 + i*10,20),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(10,7 + i*10,20),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(20,7 + i*10,20),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
			
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-10,7 + i*10,-20),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,7 + i*10,-20),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(10,7 + i*10,-20),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(20,7 + i*10,-20),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);

			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(20,7 + i*10,-10),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(20,7 + i*10,0),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(20,7 + i*10,10),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
	
		//create all the wood object in the level

			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-20,27 + i*10,-20),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-20,27 + i*10,-10),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-20,27 + i*10,0),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-20,27 + i*10,10),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-20,27 + i*10,20),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);

			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-10,27 + i*10,20),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,27 + i*10,20),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(10,27 + i*10,20),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(20,27 + i*10,20),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-10,27 + i*10,-20),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,27 + i*10,-20),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(10,27 + i*10,-20),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(20,27 + i*10,-20),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);

			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(20,27 + i*10,-10),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(20,27 + i*10,0),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(20,27 + i*10,10),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
		}
		

		//set the fixture definition for the pig object
		m_pigFixtureDefinition.m_friction = 0.9;
		m_pigFixtureDefinition.m_restitution = 0.0;
		//create all the pig object in the level
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,5,0),5,3000,m_pigFixtureDefinition,MAT_PIG);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,25,0),5,3000,m_pigFixtureDefinition,MAT_PIG);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,45,0),5,3000,m_pigFixtureDefinition,MAT_PIG);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,65,0),5,3000,m_pigFixtureDefinition,MAT_PIG);
	}

	void Level::createLevel2()
	{
		m_currentLevel =2;
		//set the fixture definition for the ice object
		m_boxFixtureDefinition.m_friction = 0.2;
		m_boxFixtureDefinition.m_restitution = 0.2;

		//set the fixture definition for the stone object
		m_boxFixtureDefinition.m_friction = 0.9;
		m_boxFixtureDefinition.m_restitution = 0.0;

		//set the fixture definition for the wood object
		m_boxFixtureDefinition.m_friction = 0.7;
		m_boxFixtureDefinition.m_restitution = 0.2;

		//set the fixture definition for the pig object
		m_pigFixtureDefinition.m_friction = 0.9;
		m_pigFixtureDefinition.m_restitution = 0.0;


		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(30,7,0),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(30,17,0),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(30,27,0),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(30,47,0),20,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(20,7,0),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(10,7,0),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);

		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,7,0),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,17,0),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,27,0),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,47,0),20,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-10,7,0),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-20,7,0),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);

		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-30,7,0),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-30,17,0),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-30,27,0),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-30,47,0),20,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);


		//create all the pig object in the level
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(15,17,0),5,3000,m_pigFixtureDefinition,MAT_PIG);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-15,17,0),5,3000,m_pigFixtureDefinition,MAT_PIG);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-30,67,0),5,3000,m_pigFixtureDefinition,MAT_PIG);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,67,0),5,3000,m_pigFixtureDefinition,MAT_PIG);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(30,67,0),5,3000,m_pigFixtureDefinition,MAT_PIG);
	}

	void Level::createLevel3()
	{
		m_currentLevel =2;
		//set the fixture definition for the ice object
		m_boxFixtureDefinition.m_friction = 0.2;
		m_boxFixtureDefinition.m_restitution = 0.2;

		//set the fixture definition for the stone object
		m_boxFixtureDefinition.m_friction = 0.9;
		m_boxFixtureDefinition.m_restitution = 0.0;

		//set the fixture definition for the wood object
		m_boxFixtureDefinition.m_friction = 0.7;
		m_boxFixtureDefinition.m_restitution = 0.2;

		//m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,27,0),10,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
		//m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,47,0),20,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
		//m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-10,7,0),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);

		for (int i =-20; i<= 20; i+=10)
		{
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(i,7,-20),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(i,7,-10),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(i,7,0),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(i,7,10),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(i,7,20),10,"Examples/Rocky",MAT_STONE,m_boxFixtureDefinition);
		}

		for (int i = 17; i<= 32; i+=5)
		{
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-15,i,-5),5,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-15,i,0),5,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-15,i,5),5,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,i,-5),5,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,i,0),5,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,i,5),5,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);

			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(15,i,-5),5,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(15,i,0),5,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(15,i,5),5,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
		}

		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-10,47,0),20,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(10,47,0),20,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);

		
		for (int i = 60; i<= 75; i+=5)
		{
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-7.5,i,-5),5,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-7.5,i,0),5,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-7.5,i,5),5,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(7.5,i,-5),5,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(7.5,i,0),5,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
			m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(7.5,i,5),5,"WoodPallet",MAT_WOOD,m_boxFixtureDefinition);
		}

		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,90,0),20,"Examples/WaterStream",MAT_ICE,m_boxFixtureDefinition);
			
		//set the fixture definition for the pig object
		m_pigFixtureDefinition.m_friction = 0.9;
		m_pigFixtureDefinition.m_restitution = 0.0;
		//create all the pig object in the level
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-10,17,0),3,3000,m_pigFixtureDefinition,MAT_PIG);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(10,17,0),3,3000,m_pigFixtureDefinition,MAT_PIG);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(-15,60,0),3,3000,m_pigFixtureDefinition,MAT_PIG);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,60,0),3,3000,m_pigFixtureDefinition,MAT_PIG);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(15,60,0),3,3000,m_pigFixtureDefinition,MAT_PIG);
		m_matFactory->CreateObject(m_uniqueIDGenerator->getNewID(),Ogre::Vector3(0,100,0),3,3000,m_pigFixtureDefinition,MAT_PIG);
	}

	bool Level::checkLevelWin()
	{
		return true;
	}

	void Level::beatLevel()
	{
		clearLevelObjectData();
		switch (getCurrentLevel())
		{
		case 1:
			m_currentLevel =2;
			createLevel2();
			break;
		case 2:
			m_currentLevel =3;
			createLevel3();
			break;
		case 3:
			m_currentLevel =1;
			createLevel1();
			break;
		}
	}

	void Level::clearLevelObjectData()
	{
		//In the base game object class, I create a deleteObject fucntion
		//So an object can be deleted by: object->deleteObject();
		//sometimes u need to check if the object has already been deleted or not
		//so before the deletion do a check: if(object->getIsDeleted)
	}

	void Level::setCurrentLevel(int newCurrentLevel)
	{
		m_currentLevel = newCurrentLevel;
	}

	int Level::getCurrentLevel()
	{
		return m_currentLevel;
	}

	std::vector<GameEntities::BoxObject*> & Level::getLevelObjectList()
	{
		return m_matFactory->getLevelObjectList();
	}

	std::vector<GameEntities::SphereObject*> & Level::getPigList()
	{
		return m_matFactory->getPigList();
	}

} // namespace GameUtilities