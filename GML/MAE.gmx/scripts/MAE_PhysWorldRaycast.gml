///MAE_PhysWorldRaycast(start, end, group, mask)
///MAE_PhysWorldRaycast(x, y, z, xto, yto, zto, group, mask)

/**
 * Description:
 *   Checks for collisions by casting a raw between 2 points, with an optional collision mask.
 *   Use the MAE_PhysWorldHit* functions to get more information about the collision.
 *
 * Arguments:
 *   [0]   - Starting point as a vector
 *   [1]   - End point as a vector
 *   [2-3] - Optional group and mask to filter collisions.
 *
 * Returns:
 *   1 on collision, 0 if nothing was hit.
 */

if(argument_count == 8) return external_call(global.MAB_WorldRaycast, argument[0], argument[1], argument[2], argument[3], argument[4], argument[5], argument[6], argument[7]);
else if(argument_count == 6) return external_call(global.MAB_WorldRaycast, argument[0], argument[1], argument[2], argument[3], argument[4], argument[5], -1, -1);
else if(argument_count == 4){
    var r_start = argument[0];
    var r_end = argument[1];
    return external_call(global.MAB_WorldRaycast, r_start[0], r_start[1], r_start[2], r_end[0], r_end[1], r_end[2], argument[2], argument[3]);
}
else if(argument_count == 2){
    var r_start = argument[0];
    var r_end = argument[1];
    return external_call(global.MAB_WorldRaycast, r_start[0], r_start[1], r_start[2], r_end[0], r_end[1], r_end[2], -1, -1);
}
return 0;
