///MAE_PhysBodyGetRotation(body)
/*
Returns a quaternion.
*/

external_call(global.MAB_BodyGetRotation, argument0);
var _x = external_call(global.MAB_Quat, 0);
var _y = external_call(global.MAB_Quat, 1);
var _z = external_call(global.MAB_Quat, 2);
var _w = external_call(global.MAB_Quat, 3);
return MAE_QuaternionCreate(_x, _y, _z, _w);
