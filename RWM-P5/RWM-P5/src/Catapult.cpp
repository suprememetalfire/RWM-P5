#include "Catapult.h"

namespace GameEntities
{
	Catapult::Catapult(Ogre::SceneManager * sceneManager, hkpWorld* world, Ogre::Vector3 position):
m_sceneManager(sceneManager),m_world(world),m_isDragPad(false),m_currentBird(0),m_birdPos(Ogre::Vector3::ZERO),m_isFired(false)
	{
		// Instantiate the unique ID generator used when creating game entities.
		m_uniqueIDGenerator = GameUtilities::UniqueIDGenerator::getInstance();

		//create a launch pad
		m_padFixtureDefinition.m_restitution = 0.0f;
		m_launchPadPos = position;
		m_launchPadHkPos(0) = m_launchPadPos.x;
		m_launchPadHkPos(1) = m_launchPadPos.y;
		m_launchPadHkPos(2) = m_launchPadPos.z;
		m_launchPad = new GameEntities::BoxObject(m_sceneManager, m_world,m_uniqueIDGenerator->getNewID(), m_launchPadPos, 10, "WoodPallet", MAT_NORMAL, m_padFixtureDefinition);
		m_launchPad->getSceneNode()->setVisible(false);

		//create an anchor
		m_anchorLeftPos = position;
		m_anchorLeftPos.y+=15;
		m_anchorLeftPos.z-=20;
		m_anchorLeftHkPos(0) = m_anchorLeftPos.x;
		m_anchorLeftHkPos(1) = m_anchorLeftPos.y;
		m_anchorLeftHkPos(2) = m_anchorLeftPos.z;
		m_anchorLeft = new GameEntities::BoxObject(m_sceneManager, m_world,m_uniqueIDGenerator->getNewID(), m_anchorLeftPos, 2, "WoodPallet", MAT_ANCHOR, m_anchorFixtureDefinition);

		//create an anotehr anchor
		m_anchorRightPos = position;
		m_anchorRightPos.y+=15;
		m_anchorRightPos.z+=20;
		m_anchorRightHkPos(0) = m_anchorRightPos.x;
		m_anchorRightHkPos(1) = m_anchorRightPos.y;
		m_anchorRightHkPos(2) = m_anchorRightPos.z;
		m_anchorRight = new GameEntities::BoxObject(m_sceneManager, m_world,m_uniqueIDGenerator->getNewID(), m_anchorRightPos, 2, "WoodPallet", MAT_ANCHOR, m_anchorFixtureDefinition);

		//create a joint links the launch pad and the anchor
		hkpStiffSpringConstraintData* m_launchAnchorJointDef = new hkpStiffSpringConstraintData(); 
		// Create constraint
		m_launchAnchorJointDef->setInWorldSpace(m_launchPad->getBody()->getTransform(), m_anchorLeft->getBody()->getTransform(), m_launchPadHkPos, m_anchorLeftHkPos);
		hkpMalleableConstraintData* m_malleable = new hkpMalleableConstraintData(m_launchAnchorJointDef);
		m_malleable->setStrength(0.01f);
		//	Create and add the constraint
		hkpConstraintInstance* m_launchAnchorJoint = new hkpConstraintInstance(m_launchPad->getBody(), m_anchorLeft->getBody(), m_malleable );
		m_world->addConstraint(m_launchAnchorJoint);
		m_launchAnchorJoint->removeReference();
		m_launchAnchorJointDef->removeReference(); 
		m_malleable->removeReference();

		//create another joint links the launch pad and the anchor
		hkpStiffSpringConstraintData* m_launchAnchorJointDef2 = new hkpStiffSpringConstraintData(); 
		// Create constraint
		m_launchAnchorJointDef2->setInWorldSpace(m_launchPad->getBody()->getTransform(), m_anchorRight->getBody()->getTransform(), m_launchPadHkPos, m_anchorRightHkPos);
		hkpMalleableConstraintData* m_malleable2 = new hkpMalleableConstraintData(m_launchAnchorJointDef2);
		m_malleable2->setStrength(0.01f);
		//	Create and add the constraint
		hkpConstraintInstance* m_launchAnchorJoint2 = new hkpConstraintInstance(m_launchPad->getBody(), m_anchorRight->getBody(), m_malleable2 );
		m_world->addConstraint(m_launchAnchorJoint2);
		m_launchAnchorJoint2->removeReference();
		m_launchAnchorJointDef2->removeReference();
		m_malleable2->removeReference();

		//create a visual representation of the left joint
		m_leftAnchorJointObject = sceneManager->createManualObject("LeftAnchorJointManual");
		DrawManualJoint(m_launchPadPos,m_anchorLeftPos,true);
		m_leftAnchorJointNode = sceneManager->getRootSceneNode()->createChildSceneNode("LeftAnchorJointNode");
		m_leftAnchorJointNode->attachObject(m_leftAnchorJointObject);

		//create a visual representation of the right joint
		m_rightAnchorJointObject = sceneManager->createManualObject("RightAnchorJointManual");
		DrawManualJoint(m_launchPadPos,m_anchorRightPos,false);
		m_rightAnchorJointNode = sceneManager->getRootSceneNode()->createChildSceneNode("RightAnchorJointNode");
		m_rightAnchorJointNode->attachObject(m_rightAnchorJointObject);
	}
	Catapult::~Catapult()
	{}
	void Catapult::DrawManualJoint(Ogre::Vector3 posOne, Ogre::Vector3 posTwo, bool isLeft)
	{
		if(isLeft)
		{
			m_leftAnchorJointObject->clear();
			m_leftAnchorJointObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
			m_leftAnchorJointObject->position(posOne);
			m_leftAnchorJointObject->position(posTwo);
			m_leftAnchorJointObject->end();
		}
		else
		{
			m_rightAnchorJointObject->clear();
			m_rightAnchorJointObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);
			m_rightAnchorJointObject->position(posOne);
			m_rightAnchorJointObject->position(posTwo);
			m_rightAnchorJointObject->end();			
		}
	}
	void Catapult::update()
	{
		m_launchPad->update();
		DrawManualJoint(Ogre::Vector3(m_launchPad->getBody()->getPosition()(0),m_launchPad->getBody()->getPosition()(1),m_launchPad->getBody()->getPosition()(2)),Ogre::Vector3(m_anchorLeft->getBody()->getPosition()(0),m_anchorLeft->getBody()->getPosition()(1),m_anchorLeft->getBody()->getPosition()(2)),true);
		DrawManualJoint(Ogre::Vector3(m_launchPad->getBody()->getPosition()(0),m_launchPad->getBody()->getPosition()(1),m_launchPad->getBody()->getPosition()(2)),Ogre::Vector3(m_anchorRight->getBody()->getPosition()(0),m_anchorRight->getBody()->getPosition()(1),m_anchorRight->getBody()->getPosition()(2)),false);
		if(m_isFired)
		{
			if(m_launchBirdJoint!= NULL && m_launchBirdJoint->getRigidBodyA()->getPosition()(0)> -280)
			{
				m_world->removeConstraint(m_launchBirdJoint);
				//m_launchBirdJoint->removeReference();
				m_launchBirdJoint = NULL;
				m_isFired = false;
			}
		}
	}
	void Catapult::attachBird(hkpRigidBody* m_birdBody)
	{
		//create a joint link the launch pad and the bird
		hkpStiffSpringConstraintData* m_launchBirdJointDef = new hkpStiffSpringConstraintData(); 
		// Create constraint
		m_launchBirdJointDef->setInWorldSpace(m_launchPad->getBody()->getTransform(), m_birdBody->getTransform(), m_launchPadHkPos, hkVector4(m_birdBody->getPosition()(0),m_birdBody->getPosition()(1),m_birdBody->getPosition()(2)));
		//	Create and add the constraint
		m_launchBirdJoint = new hkpConstraintInstance(m_launchPad->getBody(), m_birdBody, m_launchBirdJointDef);
		m_world->addConstraint(m_launchBirdJoint);
		m_launchBirdJointDef->removeReference(); 

	}
	void Catapult::launchBird()
	{
		m_isFired = true;
	}
	bool Catapult::getIsDragPad()
	{
		return m_isDragPad;
	}
	void Catapult::setIsDragPad(bool check)
	{
		m_isDragPad = check;
	}
	GameEntities::BoxObject* Catapult::getLaunchPad()
	{
		return m_launchPad;
	}
}