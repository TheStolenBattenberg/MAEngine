///MAE_PhysWorldSetGravity(x, y, z)
/*
Accepts a vector or 3 seperate reals.
*/

if(argument_count == 1){
    var vec = argument[0];
    return external_call(global.MAB_WorldSetGravity, vec[0], vec[1], vec[2]);
}
return external_call(global.MAB_WorldSetGravity, argument[0], argument[1], argument[2]);
