#pragma once

#include <MAE/Core/Types.h>
#include <xaudio2.h>
#include <x3daudio.h>

/**
** A terrible name choice. Please adobe, don't sue.
**/
class Audition {
public:
	Audition(uint flags);
	~Audition();


private:
	IXAudio2* pDev;
};