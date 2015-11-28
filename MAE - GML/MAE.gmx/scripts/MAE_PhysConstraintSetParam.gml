///MAE_PhysConstraintSetParam(constraint, param, value)

if(MAE_VectorIsVec3(argument2)) return external_call(global.MAB_ConstraintSetParam, argument0, argument1, 0, argument2[0], argument2[1], argument2[2]);
return external_call(global.MAB_ConstraintSetParam, argument0, argument1, argument2, 0, 0, 0);

