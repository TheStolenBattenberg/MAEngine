#include <MAE/FMOD/CFmod.h>

void CFmod::Init() {
	FMOD_RESULT res = FMOD::System_Create(&m_pSystem);
	if (FMODFAILED(res)) {
		return;
	}
	return;
}

void CFmod::Create() {
	FMOD_RESULT res = m_pSystem->init(m_iMaxSounds, FMOD_INIT_NORMAL, NULL);
	m_iMaxSounds = m_iMaxSounds;
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
	m_pSystem->close();
	m_pSystem->release();
	return;
}

void CFmod::Set3DSettings(float dopplerscale, float distancefactor, float rolloffscale) {
	m_fDopplerScale   = dopplerscale;
	m_fDistanceFactor = distancefactor;
	m_fRolloffScale   = rolloffscale;
	m_pSystem->set3DSettings(m_fDopplerScale, m_fDistanceFactor, m_fRolloffScale);
}

void CFmod::SetMaxSounds(uint MaxSounds) {
	m_iMaxSounds = MaxSounds;
}

void CFmod::SetMaxChannels(uint MaxChannels) {
	m_iMaxChannels = MaxChannels;
}

void CFmod::SetMaxGroups(uint MaxGroups) {
	m_iMaxGroups = MaxGroups;
}

void CFmod::SetMaxDSPs(uint MaxDSPs) {
	m_iMaxDSPs = MaxDSPs;
}

uint CFmod::GetMaxSounds() {
	return m_iMaxSounds;
}

uint CFmod::GetMaxChannels() {
	return m_iMaxChannels;
}

uint CFmod::GetMaxGroups() {
	return m_iMaxGroups;
}

uint CFmod::GetMaxDSPs() {
	return m_iMaxDSPs;
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