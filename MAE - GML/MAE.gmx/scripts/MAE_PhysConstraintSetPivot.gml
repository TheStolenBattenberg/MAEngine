///MAE_PhysConstraintSetPivot(constraint, n, pivot)

var vec = argument[2];
return external_call(global.MAB_ConstraintSetPivot, argument[0], argument[1], vec[0], vec[1], vec[2]);

