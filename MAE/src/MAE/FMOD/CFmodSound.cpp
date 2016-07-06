#include <MAE/FMOD/CFmod.h>

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

	Sound* snd;
	FMOD_RESULT res = m_pSystem->createSound(file, ModeSwitch[mode], 0, &snd->m_pVoice);
	if (FMODFAILED(res)) {
		return 0;
	}
	m_vSound.push_back(snd);
	return m_vSound.size() - 1;
}

void CFmod::SoundDestroy(uint sndIndex) {
	m_vSound[sndIndex]->m_pVoice->release();
	m_vSound[sndIndex] = NULL;
	return;
}

uint CFmod::SoundPlay(uint sndIndex) {
	FMOD_RESULT res = m_pSystem->playSound(m_vSound[sndIndex]->m_pVoice, NULL, false, &m_vSound[sndIndex]->m_pSound);
	if (FMODFAILED(res)) {
		return 0;
	}
	return 0;//m_vChannel.size() - 1;
}

void CFmod::Sound3DMinMaxDistance(uint sndIndex, float min, float max) {
	FMOD_RESULT res = m_vSound[sndIndex]->m_pVoice->set3DMinMaxDistance(min * m_fDistanceFactor, max * m_fDistanceFactor);
	if (FMODFAILED(res)) {
		return;
	}
	return;
}

void CFmod::Sound3DConeSettings(uint sndIndex, float insideangle, float outsideangle, float outsidevolume) {
	FMOD_RESULT res = m_vSound[sndIndex]->m_pVoice->set3DConeSettings(insideangle, outsideangle, outsidevolume);
	if (FMODFAILED(res)) {
		return;
	}
	return;
}