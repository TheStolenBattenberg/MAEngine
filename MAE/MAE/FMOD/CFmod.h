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

typedef FMOD::DSP          DSP;
typedef FMOD::Channel      Channel;
typedef FMOD::ChannelGroup Group;
typedef FMOD_DSP_PARAMETER_DESC DSPParam;
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

	//Sound
	sint      SoundLoad(string Filename, bool isStream);
	FMODError SoundFree(uint index);
	FMODError SoundPlay(uint index, Channel* channel);
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
	Channel*  ChannelCreate();
	FMODError ChannelDelete(Channel* channel);
	FMODError ChannelPause(Channel* channel, bool paused);
	FMODError ChannelStop(Channel* channel);
	FMODError ChannelSetPosition(Channel* channel, uint position);
	FMODError ChannelSetVolume(Channel* channel, float volume);
	FMODError ChannelSetFrequency(Channel* channel, float frequency);
	FMODError ChannelSetPitch(Channel* channel, float pitch);

	//DSP
	DSP*      DSPCreate(uint type);
	FMODError DSPDestroy(DSP* dsp);
	FMODError DSPAddToChannel(Channel* channel, DSP* dsp);
	FMODError DSPRemoveFromChannel(Channel* channel, DSP* dsp);
	FMODError DSPAddToGroup(Group* group, DSP* dsp);
	FMODError DSPRemoveFromGroup(Group* group, DSP* dsp);
	FMODError DSPSetBypass(DSP* dsp, bool bypass);
	FMODError DSPSetWetDry(DSP* dsp, float prewet, float postwet, float dry);
	FMODError DSPSetParamBool(DSP* dsp, uint param, bool value);
	FMODError DSPSetParamFloat(DSP* dsp, uint param, float value);
	FMODError DSPSetParamInt(DSP* dsp, uint param, sint value);
	uint      DSPGetParamCount(DSP* dsp);
	DSPParam* DSPGetParamInfo(DSP* dsp, uint index);
	string    DSPParamGetName(DSPParam* param);
	string    DSPParamGetLabel(DSPParam* param);
	string    DSPParamGetDescription(DSPParam* param);
private:
	FMOD::System*                m_pSystem = nullptr;
	std::vector <FMOD::Sound*>   m_pSound;
	FMOD::ChannelGroup*          m_pMasterChannel;

	uint m_iMaxChannels = 0;
	uint m_iSampleRate = 0;

	string m_lSoundType[25] = { "Unknown", "AIFF", "ASF", "DLS", "FLAC", "FM Sample Bank", "IT", "MIDI", "MOD", "MP2/MP3", "OGG", "Playlist", "RAW PCM", "S3M", "User", "WAV", "XM", "XMA", "IPhone", "ATRAC 9", "Vorbis", "Windows", "Android", "FMOD PCM", "Max" };
	FMOD_DSP_TYPE m_lDspType[6] = { FMOD_DSP_TYPE_CHORUS, FMOD_DSP_TYPE_ECHO, FMOD_DSP_TYPE_FLANGE, FMOD_DSP_TYPE_SFXREVERB, FMOD_DSP_TYPE_COMPRESSOR, FMOD_DSP_TYPE_PARAMEQ };
};
