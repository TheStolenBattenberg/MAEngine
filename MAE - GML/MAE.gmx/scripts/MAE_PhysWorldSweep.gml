///MAE_PhysWorldSweep(shape, x, y, z, xto, yto, zto, group, mask)
/*
Accepts two vectors or 6 reals.
Group and mask are optional.
*/

if(argument_count == 9) return external_call(global.MAB_WorldRaycast, argument[0], argument[1], argument[2], argument[3], argument[4], argument[5], argument[6], argument[7], argument[8]);
else if(argument_count == 7) return external_call(global.MAB_WorldRaycast, argument[0], argument[1], argument[2], argument[3], argument[4], argument[5], argument[6], -1, -1);
else if(argument_count == 5){
    var r_start = argument[1];
    var r_end = argument[2];
    return external_call(global.MAB_WorldRaycast, argument[0], r_start[0], r_start[1], r_start[2], r_end[0], r_end[1], r_end[2], argument[3], argument[4]);
}
else if(argument_count == 3){
    var r_start = argument[1];
    var r_end = argument[2];
    return external_call(global.MAB_WorldRaycast, argument[0], r_start[0], r_start[1], r_start[2], r_end[0], r_end[1], r_end[2], -1, -1);
}
return 0;
