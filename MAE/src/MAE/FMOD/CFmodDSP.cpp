#include <MAE/FMOD/CFmod.h>

DSP* CFmod::DSPCreate(uint type) {
	FMOD::DSP* dsp;
	m_pSystem->createDSPByType(m_lDspType[type], &dsp);
	return dsp;
}

FMODError CFmod::DSPDestroy(DSP* dsp) {
	dsp->disconnectAll(true, true);
	dsp->release();
	return FMODError::ERR_OKAY;
}

FMODError CFmod::DSPAddToChannel(Channel* channel, DSP* dsp) {
	channel->addDSP(0, dsp);
	return FMODError::ERR_OKAY;
}

FMODError CFmod::DSPRemoveFromChannel(Channel* channel, DSP* dsp) {
	channel->removeDSP(dsp);
	return FMODError::ERR_OKAY;
}

FMODError CFmod::DSPAddToGroup(Group* group, DSP* dsp) {
	group->addDSP(0, dsp);
	return FMODError::ERR_OKAY;
}

FMODError CFmod::DSPRemoveFromGroup(Group* group, DSP* dsp) {
	group->removeDSP(dsp);
	return FMODError::ERR_OKAY;
}

FMODError CFmod::DSPSetBypass(DSP* dsp, bool bypass) {
	dsp->setBypass(bypass);
	return FMODError::ERR_OKAY;
}

FMODError CFmod::DSPSetWetDry(DSP* dsp, float prewet, float postwet, float dry) {
	dsp->setWetDryMix(prewet, postwet, dry);
	return FMODError::ERR_OKAY;
}

FMODError CFmod::DSPSetParamBool(DSP* dsp, uint param, bool value) {
	dsp->setParameterBool(param, value);
	return FMODError::ERR_OKAY;
}

FMODError CFmod::DSPSetParamFloat(DSP* dsp, uint param, float value) {
	dsp->setParameterFloat(param, value);
	return FMODError::ERR_OKAY;
}

FMODError CFmod::DSPSetParamInt(DSP* dsp, uint param, sint value) {
	dsp->setParameterInt(param, value);
	return FMODError::ERR_OKAY;
}

uint CFmod::DSPGetParamCount(DSP* dsp) {
	int Params;
	dsp->getNumParameters(&Params);
	return Params;
}

DSPParam* CFmod::DSPGetParamInfo(DSP* dsp, uint index) {
	DSPParam* param;
	dsp->getParameterInfo(index, &param);
	return param;
}

string CFmod::DSPParamGetName(DSPParam* param) {
	return param->name;
}

string CFmod::DSPParamGetLabel(DSPParam* param) {
	return param->label;
}

string CFmod::DSPParamGetDescription(DSPParam* param) {
	return param->description;
}
