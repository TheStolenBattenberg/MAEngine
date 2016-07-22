#include <MAE/FMOD/CFmod.h>

FMODError CFmod::SystemCreate() {
	FMOD::System_Create(&m_pSystem);

	return FMODError::ERR_OKAY;
}

FMODError CFmod::SystemSetMaxChannels(uint MaxChannels) {
	m_iMaxChannels = MaxChannels;

	return FMODError::ERR_OKAY;
}

FMODError CFmod::SystemInitialize() {
	m_pSystem->init(m_iMaxChannels, FMOD_INIT_NORMAL, NULL);
	m_pSystem->getMasterChannelGroup(&m_pMasterChannel);

	return FMODError::ERR_OKAY;
}

FMODError CFmod::SystemUpdate() {
	m_pSystem->update();

	return FMODError::ERR_OKAY;
}

FMODError CFmod::SystemShutdown() {
	while (!m_pSound.empty()) {
		m_pSound.back()->release();
		m_pSound.pop_back();
	}
	m_pSystem->close();
	m_pSystem->release();
}

FMODError CFmod::SystemSetSoftwareFormat(uint SampleRate, uint SpeakerMode) {
	m_iSampleRate = SampleRate;
	m_pSystem->setSoftwareFormat(m_iSampleRate, (FMOD_SPEAKERMODE)SpeakerMode, FMOD_MAX_CHANNEL_WIDTH);
}

uint CFmod::SystemGetSampleRate() {
	return m_iSampleRate;
}

float CFmod::SystemGetCPUUsage() {
	float CPUUsage;
		m_pSystem->getCPUUsage(NULL, NULL, NULL, NULL, &CPUUsage);
	return CPUUsage;
}

uint CFmod::SystemGetSounds() {
	return m_pSound.size() - 1;
}

uint CFmod::SystemGetChannels() {
	return m_pChannel.size() - 1;
}