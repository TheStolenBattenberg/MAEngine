#include <MAE/FMOD/CFmod.h>


void CFmod::Channel3DAttributes(uint sndIndex, float posx, float posy, float posz, float velx, float vely, float velz) {
	FMOD_VECTOR sndposition{ posx, posy, posz };
	FMOD_VECTOR sndvelocity{ velx, vely, velz };

	m_vSound[sndIndex]->m_pSound->set3DAttributes(&sndposition, &sndvelocity);
	return;
}