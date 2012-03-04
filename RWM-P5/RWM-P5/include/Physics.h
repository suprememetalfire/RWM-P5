#pragma once

#include "havok.h"


//
// Forward declarations
//

class Physics
{
	static Physics * m_instance;			//!< A pointer to the singleton instance.
	hkpWorld* physicsWorld;
	hkJobQueue* jobQueue;
	hkJobThreadPool* threadPool;


public:
	/*! 
		*	Returns the instance of the singleton, and initialises
		*	it if it hasn't been already.
		*
		*	@return Instance of the singleton.
		*/
	static Physics * getInstance();
	
	Physics(void);
	~Physics(void);

	hkpWorld* GetPhysicsWorld(){return physicsWorld;}
	void SetUp(void);
	
	void Simulate(float);
	void TidyUp(void);
	
};


