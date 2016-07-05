#pragma once

#include <fmod.hpp>
#include <vector>

#include <MAE/Core/Types.h>
class CFmod {
public:
	void Init();
	void Create(uint MaxVoices);
	void Update();
	void Shutdown();

	uint SoundCreate(string file, uint mode);
	void SoundDestroy(uint index);
	uint SoundPlay(uint sndIndex);
	uint GetMaxVoices();

	uint DSPCreate(uint type);
	uint DSPActivate(uint dsp_index);
	
	uint ChannelAddDSP(uint channelIndex, uint dspIndex);
	uint ChannelSetDSPPosition(uint channelIndex, uint position);


	float GetCPUUsage(uint usagefactor);

private:
	FMOD::System* m_pSystem;

	uint m_iMaxVoices;
	uint m_iMaxChannels;
	uint m_iMaxGroups;

	std::vector<FMOD::Sound*> m_vSound;
	std::vector<FMOD::Channel*> m_vChannel;
	std::vector<FMOD::ChannelGroup*> m_vGroup;
	std::vector<FMOD::DSP*> m_vDSP;
};

extern CFmod* mafmod;