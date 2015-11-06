///MAE_PhysBodyGetTransform(body)
/*
Returns a matrix.
*/

var _pos = MAE_PhysBodyGetPosition(argument0);
//var _rot = MAE_PhysBodyGetRotationEuler(argument0);
//var _mat_r = MAE_MatrixCreateRotation(4, -_rot[0], -_rot[1], -_rot[2]);
var _rot = MAE_PhysBodyGetRotationQuat(argument0);
var _mat_r = MAE_MatrixCreateRotationQuaternion(4, _rot);
var _mat_p = MAE_MatrixCreateTranslation(_pos);
return MAE_MatrixMultiplyMatrix(_mat_r, _mat_p);
