#include <MAE/FMOD/CFmod.h>

sint CFmod::SoundLoad(string Filename, bool isStream) {
	FMOD::Sound* snd;
	if (!isStream) {
		m_pSystem->createSound(Filename, FMOD_DEFAULT, NULL, &snd);
		m_pSound.push_back(snd);
		return m_pSound.size() - 1;
	}
	else {
		m_pSystem->createStream(Filename, FMOD_DEFAULT, NULL, &snd);
		m_pSound.push_back(snd);
		return m_pSound.size() - 1;
	}
	return -1;
}

FMODError CFmod::SoundFree(uint index) {
	m_pSound[index]->release();
	m_pSound[index] = NULL;
	return FMODError::ERR_OKAY;
}

FMODError CFmod::SoundPlay(uint index, uint channel) {
	m_pSystem->playSound(m_pSound[index], NULL, false, &m_pChannel[channel]);
	return FMODError::ERR_OKAY;
}

FMODError CFmod::SoundSetLoopMode(uint index, uint mode) {
	switch (mode) {
	case 0:
		m_pSound[index]->setMode(FMOD_LOOP_OFF);
		return FMODError::ERR_OKAY;
		break;
	case 1:
		m_pSound[index]->setMode(FMOD_LOOP_NORMAL);
		return FMODError::ERR_OKAY;
		break;
	case 2:
		m_pSound[index]->setMode(FMOD_LOOP_BIDI);
		return FMODError::ERR_OKAY;
		break;
	}
	return FMODError::ERR_FAIL;
}

FMODError CFmod::SoundSetLoopPoints(uint index, uint start, uint end) {
	m_pSound[index]->setLoopPoints(start, FMOD_TIMEUNIT_PCM, end, FMOD_TIMEUNIT_PCM);
	return FMODError::ERR_OKAY;
}

string CFmod::SoundGetType(uint index) {
	FMOD_SOUND_TYPE type;
	m_pSound[index]->getFormat(&type, NULL, NULL, NULL);
	return m_lSoundType[(int)type];
}