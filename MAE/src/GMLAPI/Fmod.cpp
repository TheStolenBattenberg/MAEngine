#include <MAE/Main.h>
#include <MAE/Core/Types.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

#include <MAE/FMOD/CFmod.h>

CFmod* mafmod = nullptr;

//System
DLLEXPORT double MAE_FmodCreate() {
	mafmod = new CFmod();
	return (double)mafmod->SystemCreate();
}

DLLEXPORT double MAE_FmodInitialize() {
	return (double)mafmod->SystemInitialize();
}

DLLEXPORT double MAE_FmodUpdate() {
	return (double)mafmod->SystemUpdate();
}

DLLEXPORT double MAE_FmodShutdown() {
	delete mafmod;
	return (double)mafmod->SystemShutdown();
}

DLLEXPORT double MAE_FmodSetSoftwareFormat(double SampleRate, double SpeakerMode) {
	return mafmod->SystemSetSoftwareFormat((uint)SampleRate, (uint)SpeakerMode);
}

DLLEXPORT double MAE_FmodSetMaxChannels(double MaxChannels) {
	return mafmod->SystemSetMaxChannels((uint)MaxChannels);
}

DLLEXPORT double MAE_FmodGetSampleRate() {
	return (double)mafmod->SystemGetSampleRate();
}

DLLEXPORT double MAE_FmodGetCPUUsage() {
	return (double)mafmod->SystemGetCPUUsage();
}

DLLEXPORT double MAE_FmodGetSounds() {
	return (double)mafmod->SystemGetSounds();
}

//Sound - Make this use pointers
DLLEXPORT double MAE_FmodSoundLoad(string filename, double isStreamed) {
	bool chk[2]{ false, true };
	return (double)mafmod->SoundLoad(filename, chk[(uint)isStreamed]);
}

DLLEXPORT double MAE_FmodSoundFree(double index) {
	return (double)mafmod->SoundFree((uint)index);
}

DLLEXPORT double MAE_FmodSoundPlay(double index, double channel) {
	TRYBEG();
	auto ptr = doubleToPtr<Channel>(channel);
	return (double)mafmod->SoundPlay((uint)index, ptr);
	TRYEND(0);
}

DLLEXPORT double MAE_FmodSoundSetLoopMode(double index, double loopmode) {
	return (double)mafmod->SoundSetLoopMode((uint)index, (uint)loopmode);
}

DLLEXPORT double MAE_FmodSoundSetLoopPoints(double index, double start, double end) {
	return (double)mafmod->SoundSetLoopPoints((uint)index, (uint)start, (uint)end);
}

DLLEXPORT string MAE_FmodSoundGetType(double index) {
	return mafmod->SoundGetType((uint)index);
}

//Channels
DLLEXPORT double MAE_FmodChannelCreate() {
	TRYBEG();
	return ptrToDouble(mafmod->ChannelCreate());
	TRYEND(0);
}

DLLEXPORT double MAE_FmodChannelDelete(double channel) {
	TRYBEG();
		auto ptr = doubleToPtr<Channel>(channel);
		return mafmod->ChannelDelete(ptr);
	TRYEND(0);
}

DLLEXPORT double MAE_FmodChannelPause(double channel, double paused) {
	TRYBEG();
		bool chk[2]{ false, true };
		auto ptr = doubleToPtr<Channel>(channel);

		return mafmod->ChannelPause(ptr, chk[(uint)paused]);
	TRYEND(0);
}

DLLEXPORT double MAE_FmodChannelStop(double channel) {
	TRYBEG();
		auto ptr = doubleToPtr<Channel>(channel);
		return mafmod->ChannelStop(ptr);
	TRYEND(0);
}

DLLEXPORT double MAE_FmodChannelSetPosition(double channel, double position) {
	TRYBEG();
		auto ptr = doubleToPtr<Channel>(channel);
		return mafmod->ChannelSetPosition(ptr, (uint)position);
	TRYEND(0);
}

DLLEXPORT double MAE_FmodChannelSetVolume(double channel, double volume) {
	TRYBEG();
		auto ptr = doubleToPtr<Channel>(channel);
		return mafmod->ChannelSetVolume(ptr, (float)volume);
	TRYEND(0);
}

DLLEXPORT double MAE_FmodChannelSetFrequency(double channel, double frequency) {
	TRYBEG();
		auto ptr = doubleToPtr<Channel>(channel);
		return mafmod->ChannelSetFrequency(ptr, (float)frequency);
	TRYEND(0);
}

DLLEXPORT double MAE_FmodChannelSetPitch(double channel, double pitch) {
	TRYBEG();
		auto ptr = doubleToPtr<Channel>(channel);
		return mafmod->ChannelSetPitch(ptr, (float)pitch);
	TRYEND(0);
}

//DSP