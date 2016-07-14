#define MAE_PhysBodyGetRotationMatrix
var _rot = MAE_PhysBodyGetRotationQuat(argument0);
return MAE_MatrixCreateRotationQuaternion(4, _rot);

#define MAE_PhysBodyGetTransform
var _pos = MAE_PhysBodyGetPosition(argument0);
var _rot = MAE_PhysBodyGetRotationQuat(argument0);
var _mat_r = MAE_MatrixCreateRotationQuaternion(4, _rot);
var _mat_p = MAE_MatrixCreateTranslation(_pos);
return MAE_MatrixMultiplyMatrix(_mat_r, _mat_p);

#define MAE_PhysBodyIsDynamic
return !(MAE_PhysBodyIsStatic(argument0) || MAE_PhysBodyIsKinematic(argument0));

