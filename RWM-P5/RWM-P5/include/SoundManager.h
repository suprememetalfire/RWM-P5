#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "fmod.hpp" //fmod c++ header
#pragma comment( lib, "fmodex_vc.lib" ) // fmod library

const float DISTANCEFACTOR = 1.0f;          // Units per meter.

class SoundManager{
public:
	SoundManager()
	{
	//=======================================================================================
	//init FMOD
    FMOD_RESULT r = FMOD::System_Create(&system);// create an instance of the game engine
    r=system->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels
	bool             listenerflag = true;

    //load sounds
	r = system->createSound("..\\..\\Audio\\Angry Birds Theme Song.mp3", FMOD_SOFTWARE, 0, &bgm);
	bgm->setMode(FMOD_LOOP_NORMAL);   
	system->playSound(FMOD_CHANNEL_FREE, bgm, false, 0);
	r = system->createSound("..\\..\\Audio\\babyLaunch.mp3", FMOD_SOFTWARE, 0, &babyLaunch);
	r = system->createSound("..\\..\\Audio\\Select.mp3", FMOD_SOFTWARE, 0, &select);
	r = system->createSound("..\\..\\Audio\\birdHit.mp3", FMOD_SOFTWARE, 0, &birdHit);
	r = system->createSound("..\\..\\Audio\\rockHit.mp3", FMOD_SOFTWARE, 0, &rockHit);
	r = system->createSound("..\\..\\Audio\\shot.mp3", FMOD_SOFTWARE, 0, &shot);
	r = system->createSound("..\\..\\Audio\\stretch.mp3", FMOD_SOFTWARE, 0, &stretch);
	r = system->createSound("..\\..\\Audio\\woodBreak.mp3", FMOD_SOFTWARE, 0, &woodHit);
	/* drumloop.wav has embedded loop points which automatically makes looping turn on, */                                                                            /* so turn it off here.  We could have also just put FMOD_LOOP_OFF in the above CreateSound call. */
    //r = system->createSound("C:/FMOD/examples/media/swish.wav", FMOD_SOFTWARE, 0, &sound2);
	//sound2->set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 10.0f * DISTANCEFACTOR);
	//sound2->setMode(FMOD_LOOP_BIDI);
	//===========================================================================================
	}

	void update()
	{
		//FMOD_VECTOR pos = { -10.0f * DISTANCEFACTOR, 0.0f, 0.0f };
		//FMOD_VECTOR vel = {  0.0f, 0.0f, 0.0f };

		FMOD_VECTOR listenerpos = {0.0f,0.0f,0.0f};		

		system->update();
	}

	void playBabyLaunch()
	{
		system->playSound(FMOD_CHANNEL_FREE, babyLaunch, false, 0);
	}

	void playBirdSelected()
	{
		system->playSound(FMOD_CHANNEL_FREE, select, false, 0);
	}

	void playBirdHit()
	{
		system->playSound(FMOD_CHANNEL_FREE, birdHit, false, 0);
	}

	void playRockHit()
	{
		system->playSound(FMOD_CHANNEL_FREE, rockHit, false, 0);
	}

	void playShot()
	{
		system->playSound(FMOD_CHANNEL_FREE, shot, false, 0);
	}

	void playStretch()
	{
		system->playSound(FMOD_CHANNEL_FREE, stretch, false, 0);
	}

	void playWoodHit()
	{
		system->playSound(FMOD_CHANNEL_FREE, woodHit, false, 0);
	}

private:
protected:

		//==========================================================================
	//FMod Stuff
    FMOD::System     *system; //handle to FMOD engine
    FMOD::Sound      *bgm, *babyLaunch, *select, *birdHit, *rockHit, *shot, *stretch, *woodHit;//sound that will be loaded and played
	FMOD_VECTOR      *listenerpos;
	//===========================================================================
};

#endif
