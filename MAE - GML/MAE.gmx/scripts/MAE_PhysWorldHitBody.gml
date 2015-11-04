//MAE_PhysWorldHitBody([n])

if(argument_count == 0) return external_call(global.MAB_HitResult, 3);
else return external_call(global.MAB_OverlapResult, argument[0]);
