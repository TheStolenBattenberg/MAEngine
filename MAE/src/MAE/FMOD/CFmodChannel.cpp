#include <MAE/FMOD/CFmod.h>

Channel* CFmod::ChannelCreate() {
	Channel* chn = NULL;
	return chn;
}

FMODError CFmod::ChannelDelete(Channel* channel) {
	channel->stop();
	delete channel;
	return FMODError::ERR_OKAY;
}

FMODError CFmod::ChannelPause(Channel* channel, bool paused) {
	channel->setPaused(paused);
	return FMODError::ERR_OKAY;
}

FMODError CFmod::ChannelStop(Channel* channel) {
	channel->stop();
	return FMODError::ERR_OKAY;
}

FMODError CFmod::ChannelSetPosition(Channel* channel, uint position) {
	channel->setPosition(position, FMOD_TIMEUNIT_PCM);
	return FMODError::ERR_OKAY;
}

FMODError CFmod::ChannelSetVolume(Channel* channel, float volume) {
	channel->setVolume(volume);
	return FMODError::ERR_OKAY;
}

FMODError CFmod::ChannelSetFrequency(Channel* channel, float frequency) {
	channel->setFrequency(frequency);
	return FMODError::ERR_OKAY;
}

FMODError CFmod::ChannelSetPitch(Channel* channel, float pitch) {
	channel->setPitch(pitch);
	return FMODError::ERR_OKAY;
}