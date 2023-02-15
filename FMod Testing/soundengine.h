
#pragma once

#include <string>
#include <iostream>
#include "ext_headers/fmod.h"
#include "ext_headers/fmod_errors.h"
#include <windows.h>

class CSoundEngine {

private:

	//init functions
	decltype(FMOD_System_Create)* pFMOD_System_Create;
	decltype(FMOD_System_Init)* pFMOD_System_Init;

	//channel functions
	decltype(FMOD_System_GetChannel)* pFMOD_System_GetChannel;
	decltype(FMOD_Channel_Stop)* pFMOD_Channel_Stop;
	decltype(FMOD_Channel_IsPlaying)* pFMOD_Channel_IsPlaying;

	//sound play functions
	decltype(FMOD_System_CreateStream)* pFMOD_System_CreateStream;
	decltype(FMOD_System_PlaySound)* pFMOD_System_PlaySound;

	//upkeep functions
	decltype(FMOD_System_Update)* pFMOD_System_Update;


	HINSTANCE m_hFMod;

	FMOD_RESULT fmResult;
	FMOD_SYSTEM* fmSystem = NULL;
	FMOD_CHANNEL* fmChannel = NULL;
	FMOD_SOUND* fmStream = NULL;
	FMOD_BOOL fm_bIsPlaying;

	bool	m_iIsPlaying;

	char m_szMP3File[128];

	float	m_flFadeoutStart;
	float	m_flFadeoutDuration;

public:
	int		Initialize();
	bool	PlaySoundStream(std::string filename);
	bool	StopSound();
};