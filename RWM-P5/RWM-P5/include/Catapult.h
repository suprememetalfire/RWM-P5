#ifndef CATAPULT_H
#define CATAPULT_H

#include "UniqueIDGenerator.h"
#include "BoxObject.h"
#include "BaseBirdObject.h"
#include <OgreManualObject.h>
// We will need these collision agents
#include <Physics/Collide/Agent/ConvexAgent/BoxBox/hkpBoxBoxAgent.h>

// We need to create a constraint
#include <Physics/Dynamics/Constraint/Bilateral/StiffSpring/hkpStiffSpringConstraintData.h>

#include <Physics/Dynamics/Constraint/Malleable/hkpMalleableConstraintData.h>

// We want to turn on constraint viewers for this demo
#include <Physics/Utilities/VisualDebugger/Viewer/Dynamics/hkpConstraintViewer.h>

namespace GameEntities
{
	class Catapult
	{
	private:
		GameUtilities::UniqueIDGenerator * m_uniqueIDGenerator;
		//pointer to the Ogre scene manager
		Ogre::SceneManager *m_sceneManager;
		//pointer to the Box2D
		hkpWorld *m_world;

//--------------------------The Launch Pad----------------------------
		//create the launch pad
		GameEntities::BoxObject* m_launchPad;
			//launch pad position
		Ogre::Vector3 m_launchPadPos;
			//launch pad hk position
		hkVector4 m_launchPadHkPos;
			//launch pad fixture definition
		hkpRigidBodyCinfo m_padFixtureDefinition;
//--------------------------The Left Anchor----------------------------
		//create the anchor
		GameEntities::BoxObject* m_anchorLeft;
			//anchor position
		Ogre::Vector3 m_anchorLeftPos;
			//anchor hk position
		hkVector4 m_anchorLeftHkPos;
			//anchor fixture definition
		hkpRigidBodyCinfo m_anchorFixtureDefinition;
//--------------------------The Right Anchor----------------------------
		//create the anchor
		GameEntities::BoxObject* m_anchorRight;
			//anchor position
		Ogre::Vector3 m_anchorRightPos;
			//anchor hk position
		hkVector4 m_anchorRightHkPos;
//--------------------------The Left Anchor Manual Object---------------------------
		//the scene node for this joint manual object
		Ogre::SceneNode * m_leftAnchorJointNode;
		//create the 2D manual object for the joint
		Ogre::ManualObject * m_leftAnchorJointObject;
//--------------------------The Right Anchor Manual Object---------------------------
		//the scene node for this joint manual object
		Ogre::SceneNode * m_rightAnchorJointNode;
		//create the 2D manual object for the joint
		Ogre::ManualObject * m_rightAnchorJointObject;
//--------------------------The Launch Pad-Bird Joint-------------------------
		//the joint fixture definition
		//hkpStiffSpringConstraintData* m_launchBirdJointDef;
		//create the joint which links the launch pad and the bird
		hkpConstraintInstance* m_launchBirdJoint;
//----------------------------------------------------------------------------

		//create a pointer to the cuurent attached bird
		GameEntities::BaseBirdObject* m_currentBird;
		//the bird position
		Ogre::Vector3 m_birdPos;

		bool m_isDragPad;
		bool m_isFired;

		void DrawManualJoint(Ogre::Vector3 posOne, Ogre::Vector3 posTwo,bool isLeft);
	public:
		/*!	Constructor.
			 * 
			 *	Creates an instance of the Catapult, and sets up its varies properties.
			 *
			 * @param sceneManager A pointer to the SceneManager, used for creating Ogre
			 * Entities and SceneNodes.
			 * @param world The Box2D World object, used for creating bodies and fixtures.
			 * @param objectID The unique ID for this instance.
			 * @param position Initial position for this object.
			 * @param halfWidth Half the desired width of the box.
			 * @param halfHeight Half the desired height of the box.
			 * @param fixtureDefinition Fixture definition describing the properties of the
			 * box.
			 */
		Catapult(Ogre::SceneManager * sceneManager, hkpWorld* world, Ogre::Vector3 position);
		~Catapult();
		void update();
		void attachBird(hkpRigidBody* m_birdBody);
		void launchBird();
		//getter and setter
		bool getIsDragPad();
		void setIsDragPad(bool check);
		GameEntities::BoxObject* getLaunchPad();
	}; // class Catpult
}

#endif