#pragma once

#include <fmod.hpp>
#include <vector>

#include <MAE/Core/Types.h>

enum FMODError {
	ERR_OKAY     =  0x00,
	ERR_FAIL     = -0x01,
	ERR_INIT     = -0x02,
	ERR_CREATE   = -0x03,
	ERR_UPDATE   = -0x04,
	ERR_SHUTDOWN = -0x05
};

/**
 * Notes (TSB): I've yet to make this not use vectors for storing the sounds etc, but that's next on the list.
 */


class CFmod {
public:
	//System
	FMODError SystemCreate();
	FMODError SystemInitialize();
	FMODError SystemUpdate();
	FMODError SystemShutdown();
	FMODError SystemSetSoftwareFormat(uint SampleRate, uint SpeakerMode);
	FMODError SystemSetMaxChannels(uint MaxChannels);
	uint      SystemGetSampleRate();
	float     SystemGetCPUUsage();
	uint      SystemGetSounds();
	uint      SystemGetChannels();

	//Sound
	sint      SoundLoad(string Filename, bool isStream);
	FMODError SoundFree(uint index);
	FMODError SoundPlay(uint index, uint channel);
	FMODError SoundSetLoopMode(uint index, uint mode);
	FMODError SoundSetLoopPoints(uint index, uint start, uint end);
	string    SoundGetType(uint index);

	//Unsure about implementing this.
	uint      SoundGetTagNumber(uint index); 
	string    SoundGetTagName(uint index, uint tagIndex);
	string    SoundGetTagType(uint index, uint tagIndex);
	string    SoundGetTagDataType(uint index, uint tagIndex);
	double    SoundGetTagReal(uint index, string tagName);
	string    SoundGetTagString(uint index, string tagName);

	//Channel
	sint      ChannelCreate();
	FMODError ChannelDelete(uint index);
	FMODError ChannelPause(uint index, bool paused);
	FMODError ChannelStop(uint index);
	FMODError ChannelSetPosition(uint index, uint position);
	FMODError ChannelSetVolume(uint index, float volume);
	FMODError ChannelSetFrequency(uint index, float frequency);
	FMODError ChannelSetPitch(uint index, float pitch);

private:
	FMOD::System*                m_pSystem;
	std::vector <FMOD::Sound*>   m_pSound;
	std::vector <FMOD::Channel*> m_pChannel;
	FMOD::ChannelGroup*          m_pMasterChannel;

	uint m_iMaxChannels;
	uint m_iSampleRate;

	string m_lSoundType[25] = { "Unknown", "AIFF", "ASF", "DLS", "FLAC", "FM Sample Bank", "IT", "MIDI", "MOD", "MP2/MP3", "OGG", "Playlist", "RAW PCM", "S3M", "User", "WAV", "XM", "XMA", "IPhone", "ATRAC 9", "Vorbis", "Windows", "Android", "FMOD PCM", "Max" };
};

extern CFmod* mafmod;