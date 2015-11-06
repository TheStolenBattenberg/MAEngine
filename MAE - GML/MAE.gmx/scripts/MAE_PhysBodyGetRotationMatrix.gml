///MAE_PhysBodyGetRotationMatrix(body)

var _rot = MAE_PhysBodyGetRotationQuat(argument0);
return MAE_MatrixCreateRotationQuaternion(4, _rot);
