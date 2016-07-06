#pragma once

#include <fmod.hpp>

struct Sound {
	FMOD::Sound*        m_pVoice;
	FMOD::Channel*      m_pSound;
	uint                m_iGroupIndex;
};