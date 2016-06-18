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

private:
	FMOD::System* m_pSystem;

	uint m_iMaxVoices;
	uint m_iMaxChannels;

	std::vector<FMOD::Sound*> m_vVoices;
	std::vector<FMOD::Channel*> m_vInstance;
	std::vector<FMOD::ChannelGroup*> m_vChannel;
};

extern CFmod* mafmod;