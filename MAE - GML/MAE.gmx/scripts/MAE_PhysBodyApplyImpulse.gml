///MAE_PhysBodyApplyImpulse(body, x, y, z, xvel, yvel, zvel)
/*
Accepts 2 vectors or 6 seperate reals.
*/

if(argument_count == 3){
    var vec = argument[1];
    var vec2 = argument[2];
    return external_call(global.MAB_BodySetApplyImpulse, argument[0], vec[0], vec[1], vec[2], vec2[0], vec2[1], vec2[2]);
}
return external_call(global.MAB_BodyApplyImpulse, argument[0], argument[1], argument[2], argument[3], argument[4], argument[5], argument[6]);
