///MAE_PhysWorldOverlap(shape, x, y, z, quaternion, [group, mask])
///MAE_PhysWorldOverlap(shape, vec, quaternion, [group, mask])
/*
Returns the number of bodies that the shape overlaps.
Call MAE_PhysWorldHitBody(n) to get the bodies.
*/

if(is_array(argument[1])){
    var vec = argument[1];
    var quat = argument[2];
    if(argument_count > 3) return external_call(global.MAB_WorldOverlap, argument[0], vec[0], vec[1], vec[2], quat[0], quat[1], quat[2], quat[3], argument[3], argument[4]);
    else return external_call(global.MAB_WorldOverlap, argument[0], vec[0], vec[1], vec[2], quat[0], quat[1], quat[2], quat[3], -1, -1);
}
else{
    var quat = argument[4];
    if(argument_count > 5) external_call(global.MAB_WorldOverlap, argument[0], argument[1], argument[2], argument[3], quat[0], quat[1], quat[2], quat[3], argument[5], argument[6]);
    else return external_call(global.MAB_WorldOverlap, argument[0], argument[1], argument[2], argument[3], quat[0], quat[1], quat[2], quat[3], -1, -1);
}
