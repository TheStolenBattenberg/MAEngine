///MAE_PhysBodySetLinearFactor(body, x, y, z)
/*
Accepts a vector, a single real that applies to each axis, or 3 seperate reals.
*/

if(argument_count == 2){
    var vec = argument[1];
    if(MAE_VectorIsVec3(vec)) return external_call(global.MAB_BodySetLinearFactor, argument[0], vec[0], vec[1], vec[2]);
    else return external_call(global.MAB_BodySetLinearFactor, argument[0], vec, vec, vec);
}
return external_call(global.MAB_BodySetLinearFactor, argument[0], argument[1], argument[2], argument[3]);
