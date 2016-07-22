#include <MAE/FMOD/CFmod.h>

sint CFmod::ChannelCreate() {
	FMOD::Channel* chn;
	m_pChannel.push_back(chn);
	return m_pChannel.size() - 1;
}

FMODError CFmod::ChannelDelete(uint index) {
	m_pChannel[index]->stop();
	m_pChannel[index] = NULL;
	return FMODError::ERR_OKAY;
}

FMODError CFmod::ChannelPause(uint index, bool paused) {
	m_pChannel[index]->setPaused(paused);
	return FMODError::ERR_OKAY;
}

FMODError CFmod::ChannelStop(uint index) {
	m_pChannel[index]->stop();
	return FMODError::ERR_OKAY;
}

FMODError CFmod::ChannelSetPosition(uint index, uint position) {
	m_pChannel[index]->setPosition(position, FMOD_TIMEUNIT_PCM);
	return FMODError::ERR_OKAY;
}

FMODError CFmod::ChannelSetVolume(uint index, float volume) {
	m_pChannel[index]->setVolume(volume);
	return FMODError::ERR_OKAY;
}

FMODError CFmod::ChannelSetFrequency(uint index, float frequency) {
	m_pChannel[index]->setFrequency(frequency);
	return FMODError::ERR_OKAY;
}

FMODError CFmod::ChannelSetPitch(uint index, float pitch) {
	m_pChannel[index]->setPitch(pitch);
	return FMODError::ERR_OKAY;
}