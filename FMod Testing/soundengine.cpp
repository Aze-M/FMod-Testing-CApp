
#include "soundengine.h"

int CSoundEngine::Initialize() {

	m_hFMod = LoadLibraryW(L".\\dlls\\fmod.dll");

	if (m_hFMod != NULL) {

		//commands for making and initializing the system
		pFMOD_System_Create = reinterpret_cast<decltype(pFMOD_System_Create)>(GetProcAddress(m_hFMod, "FMOD_System_Create"));
		pFMOD_System_Init = reinterpret_cast<decltype(pFMOD_System_Init)>(GetProcAddress(m_hFMod, "FMOD_System_Init"));

		//channel functions
		pFMOD_System_GetChannel = reinterpret_cast<decltype(pFMOD_System_GetChannel)>(GetProcAddress(m_hFMod, "FMOD_System_GetChannel"));
		pFMOD_Channel_Stop = reinterpret_cast<decltype(pFMOD_Channel_Stop)>(GetProcAddress(m_hFMod, "FMOD_Channel_Stop"));
		pFMOD_Channel_IsPlaying = reinterpret_cast<decltype(pFMOD_Channel_IsPlaying)>(GetProcAddress(m_hFMod, "FMOD_Channel_IsPlaying"));

		//playback functions
		pFMOD_System_CreateStream = reinterpret_cast<decltype(pFMOD_System_CreateStream)>(GetProcAddress(m_hFMod, "FMOD_System_CreateStream"));
		pFMOD_System_PlaySound = reinterpret_cast<decltype(pFMOD_System_PlaySound)>(GetProcAddress(m_hFMod, "FMOD_System_PlaySound"));

		//upkeep functions
		pFMOD_System_Update = reinterpret_cast<decltype(pFMOD_System_Update)>(GetProcAddress(m_hFMod, "FMOD_System_Update"));
	}

	//start the fmod system
	fmResult = pFMOD_System_Create(&fmSystem, FMOD_VERSION);

	if (fmResult != FMOD_OK) {
		std::cout << FMOD_ErrorString(fmResult) << std::endl;
		return 0;
	}

	std::cout << FMOD_ErrorString(fmResult) << std::endl;

	//init an fmod system with 1 channel
	fmResult = pFMOD_System_Init(fmSystem, 1, FMOD_INIT_NORMAL, 0);

	if (fmResult != FMOD_OK) {
		std::cout << FMOD_ErrorString(fmResult) << std::endl;
		return 0;
	}

	std::cout << FMOD_ErrorString(fmResult) << std::endl;

	return 1;
}

bool CSoundEngine::PlaySoundStream(std::string filename) {

	//stop here if the dll isn't loaded
	if (!m_hFMod) {
		return false;
	}

	fmResult = pFMOD_System_CreateStream(fmSystem, filename.c_str(), FMOD_DEFAULT, NULL, &fmStream);

	if (fmResult != FMOD_OK) {
		std::cout << FMOD_ErrorString(fmResult) << std::endl;
		return false;
	}

	std::cout << FMOD_ErrorString(fmResult) << std::endl;

	fmResult = pFMOD_System_PlaySound(fmSystem, fmStream, NULL, false, &fmChannel);

	if (fmResult != FMOD_OK) {
		std::cout << FMOD_ErrorString(fmResult) << std::endl;
		return false;
	}

	std::cout << FMOD_ErrorString(fmResult) << std::endl;

	if (fmResult != FMOD_OK) {
		std::cout << FMOD_ErrorString(fmResult) << std::endl;
		return false;
	}

	std::cout << FMOD_ErrorString(fmResult) << std::endl;

	//update
	fmResult = pFMOD_System_Update(fmSystem);

	if (fmResult != FMOD_OK) {
		std::cout << FMOD_ErrorString(fmResult) << std::endl;
		return false;
	}

	std::cout << FMOD_ErrorString(fmResult) << std::endl;

	//and keep doing it if we're playing
	fmResult = pFMOD_Channel_IsPlaying(fmChannel, &fm_bIsPlaying);

	if (fmResult != FMOD_OK) {
		std::cout << FMOD_ErrorString(fmResult) << std::endl;
		return false;
	}

	std::cout << FMOD_ErrorString(fmResult) << std::endl;

	while (fm_bIsPlaying) {
		pFMOD_System_Update(fmSystem);
		pFMOD_Channel_IsPlaying(fmChannel, &fm_bIsPlaying);
	}

	return true;
};