///MAE_PhysBodyGetGravity(body)
/*
Returns a vector.
*/

external_call(global.MAB_BodyGetGravity, argument0);
var vec;
vec[0] = external_call(global.MAB_Vec, 0);
vec[1] = external_call(global.MAB_Vec, 1);
vec[2] = external_call(global.MAB_Vec, 2);
return vec;
