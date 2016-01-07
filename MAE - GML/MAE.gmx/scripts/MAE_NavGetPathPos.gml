///MAE_NavGetPathPos(n)

external_call(global.MA_NavGetPathPos, argument0);
var v;
v[0] = external_call(global.MA_NavGetVec, 0);
v[1] = external_call(global.MA_NavGetVec, 1);
v[2] = external_call(global.MA_NavGetVec, 2);
return v;
