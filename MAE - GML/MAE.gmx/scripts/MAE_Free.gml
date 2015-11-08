///MAE_Free()
var MADX9Free = external_call(global.MADX9_Free);
external_free(global.DLL_MADX9);

var MABulletFree = external_call(global.MAB_Free);
external_free(global.DLL_MABullet);

return MADX9Free & MABulletFree;
