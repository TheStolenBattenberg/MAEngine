#include "CFmod.h"

bool FMODFAILED(FMOD_RESULT res) {
	if (res != FMOD_OK) {
		return true;
	}
	return false;
}

void CFmod::Init() {
	FMOD_RESULT res = FMOD::System_Create(&m_pSystem);
	if (FMODFAILED(res)) {
		return;
	}
	return;
}

void CFmod::Create(uint MaxVoices) {
	FMOD_RESULT res = m_pSystem->init(MaxVoices, FMOD_INIT_NORMAL, NULL);
	if (FMODFAILED(res)) {
		return;
	}
	return;
}

void CFmod::Update() {
	m_pSystem->update();
	return;
}

void CFmod::Shutdown() {
	m_pSystem->release();
}

uint CFmod::SoundCreate(string file, uint mode) {
	FMOD_MODE ModeSwitch[12]{
		FMOD_LOOP_OFF,
		FMOD_LOOP_NORMAL,
		FMOD_LOOP_BIDI,
		FMOD_3D_HEADRELATIVE,
		FMOD_3D_WORLDRELATIVE,
		FMOD_2D,
		FMOD_3D,
		FMOD_3D_INVERSEROLLOFF,
		FMOD_3D_LINEARROLLOFF,
		FMOD_3D_LINEARSQUAREROLLOFF,
		FMOD_3D_CUSTOMROLLOFF,
		FMOD_3D_IGNOREGEOMETRY };

	FMOD::Sound* snd;
	FMOD_RESULT res = m_pSystem->createSound(file, ModeSwitch[mode], 0, &snd);
	if (FMODFAILED(res)) {
		return 0;
	}
	m_vVoices.push_back(snd);
	return m_vVoices.size() - 1;
}

void CFmod::SoundDestroy(uint index) {
	m_vVoices[index]->release();
	m_vVoices[index] = NULL;
	return;
}

uint CFmod::SoundPlay(uint sndIndex) {
	FMOD_RESULT res = m_pSystem->playSound(m_vVoices[sndIndex], m_vChannel[0], false, &m_vInstance[m_vInstance.size()]);
	if (FMODFAILED(res)) {
		return 0;
	}
	return m_vInstance.size() - 1;
}

uint CFmod::GetMaxVoices() {
	return m_iMaxVoices;
}