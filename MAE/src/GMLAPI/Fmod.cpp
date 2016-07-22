#include <MAE/Main.h>
#include <MAE/Core/Types.h>

#include <GMLAPI/Main.h>
#include <GMLAPI/Utils.h>

#include <MAE/FMOD/CFmod.h>

DLLEXPORT double MAE_FmodCreate() {
	return mafmod->SystemCreate();
}

DLLEXPORT double MAE_FmodInitialize() {
	return mafmod->SystemInitialize();
}

DLLEXPORT double MAE_FmodSetMaxChannels(double MaxChannels) {
	return mafmod->SystemSetMaxChannels((uint)MaxChannels);
}

DLLEXPORT double MAE_FmodShutdown() {
	return mafmod->SystemShutdown();
}