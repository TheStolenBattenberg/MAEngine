#pragma once

#include <fmod.hpp>
#include <vector>

#include <MAE/Core/Types.h>

#include <MAE/FMOD/CFmodHelper.h>

class CFmod {
public:
	//General
	bool FMODFAILED(FMOD_RESULT res) { if (res != FMOD_OK) { return false; } return true; }

	//CFmod.cpp
	void Init();
	void Create();
	void Update();
	void Shutdown();

	void Set3DSettings(float dopplerscale, float distancefactor, float rolloffscale);

	void SetMaxSounds(uint MaxSounds);
	uint GetMaxSounds();
	void SetMaxChannels(uint MaxChannels);
	uint GetMaxChannels();
	void SetMaxGroups(uint MaxGroups);
	uint GetMaxGroups();
	void SetMaxDSPs(uint MaxDSPs);
	uint GetMaxDSPs();

	float GetCPUUsage(uint usagefactor);

	//CFmodSound.cpp
	uint SoundCreate(string file, uint mode);
	void SoundDestroy(uint sndIndex);
	uint SoundPlay(uint sndIndex);
	void Sound3DMinMaxDistance(uint sndIndex, float min, float max);
	void Sound3DConeSettings(uint sndIndex, float insideangle, float outsideangle, float outsidevolume);
	void SoundSetGroup(uint sndIndex, uint grpIndex);

	//CFmodDSP.cpp
	uint DSPCreate(uint type);
	void DSPDestroy(uint DSPIndex);
	void DSPActivate(uint DSPIndex, bool state);
	
	//CFmodChannel.cpp
	uint ChannelAddDSP(uint sndIndex, uint dspIndex);
	uint ChannelSetDSPPosition(uint sndIndex, uint position);
	void Channel3DAttributes(uint sndIndex, float posx, float posy, float posz, float velx, float vely, float velz);

private:
	FMOD::System* m_pSystem;

	float m_fDopplerScale   = 1.0f;
	float m_fDistanceFactor = 1.0f;
	float m_fRolloffScale   = 1.0f;

	uint m_iMaxSounds;
	uint m_iMaxChannels;
	uint m_iMaxGroups;
	uint m_iMaxDSPs;

	std::vector<Sound*> m_vSound;
	std::vector<FMOD::ChannelGroup*> m_vGroup;
	std::vector<FMOD::DSP*> m_vDSP;
};

extern CFmod* mafmod;