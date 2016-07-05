#include <MAE/FMOD/CFmod.h>

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
	m_vSound.push_back(snd);
	return m_vSound.size() - 1;
}

void CFmod::SoundDestroy(uint index) {
	m_vSound[index]->release();
	m_vSound[index] = NULL;
	return;
}

uint CFmod::SoundPlay(uint sndIndex) {
	FMOD_RESULT res = m_pSystem->playSound(m_vSound[sndIndex], m_vGroup[0], false, &m_vChannel[m_vChannel.size()]);
	if (FMODFAILED(res)) {
		return 0;
	}
	return m_vChannel.size() - 1;
}

uint CFmod::DSPCreate(uint type) {
	FMOD::DSP *dsp;
	FMOD_DSP_DESCRIPTION DSPTYPE[28] {
		FMOD_DSP_TYPE_CHANNELMIX,
		FMOD_DSP_TYPE_CHORUS,
		FMOD_DSP_TYPE_COMPRESSOR,
		FMOD_DSP_TYPE_CONVOLUTIONREVERB,
		FMOD_DSP_TYPE_DELAY,
		FMOD_DSP_TYPE_DISTORTION,
		FMOD_DSP_TYPE_ECHO,
		FMOD_DSP_TYPE_ENVELOPEFOLLOWER,
		FMOD_DSP_TYPE_FADER,
		FMOD_DSP_TYPE_FLANGE,
		FMOD_DSP_TYPE_HIGHPASS,
		FMOD_DSP_TYPE_HIGHPASS_SIMPLE,
		FMOD_DSP_TYPE_ITECHO,
		FMOD_DSP_TYPE_ITLOWPASS,
		FMOD_DSP_TYPE_LIMITER,
		FMOD_DSP_TYPE_LOWPASS,
		FMOD_DSP_TYPE_LOWPASS_SIMPLE,
		FMOD_DSP_TYPE_MAX,
		FMOD_DSP_TYPE_MIXER,
		FMOD_DSP_TYPE_NORMALIZE,
		FMOD_DSP_TYPE_OBJECTPAN,
		FMOD_DSP_TYPE_PAN,
		FMOD_DSP_TYPE_PARAMEQ,
		FMOD_DSP_TYPE_PITCHSHIFT,
		FMOD_DSP_TYPE_SFXREVERB,
		FMOD_DSP_TYPE_THREE_EQ,
		FMOD_DSP_TYPE_TRANSCEIVER,
		FMOD_DSP_TYPE_TREMOLO
	};

	m_pSystem->createDSP(&DSPTYPE[type], &dsp);
	m_vDSP.push_back(dsp);
	return m_vDSP.size() - 1;
}

uint CFmod::GetMaxVoices() {
	return m_iMaxVoices;
}

float CFmod::GetCPUUsage(uint usagefactor) {
	float cpuusage;
	switch (usagefactor) {
		case 0:
			m_pSystem->getCPUUsage(&cpuusage, NULL, NULL, NULL, NULL);
			return cpuusage;

		case 1:
			m_pSystem->getCPUUsage(NULL, &cpuusage, NULL, NULL, NULL);
			return cpuusage;

		case 2:
			m_pSystem->getCPUUsage(NULL, NULL, &cpuusage, NULL, NULL);
			return cpuusage;

		case 3:
			m_pSystem->getCPUUsage(NULL, NULL, NULL, &cpuusage, NULL);
			return cpuusage;

		case 4:
			m_pSystem->getCPUUsage(NULL, NULL, NULL, NULL, &cpuusage);
			return cpuusage;

		default:
			return 0.0f;
	}
	return 0.0f;
}