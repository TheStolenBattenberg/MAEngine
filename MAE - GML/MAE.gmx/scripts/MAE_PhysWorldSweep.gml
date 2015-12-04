///MAE_PhysWorldSweep(shape, start, end, group, mask)
///MAE_PhysWorldSweep(shape, x, y, z, xto, yto, zto, group, mask)

/**
 * Description:
 *   Checks for collisions by casting a convex shape between 2 points, with an optional collision mask.
 *   Behaves like a raycast, but casts a shape instead of a point. The shape must be a convex shape.
 *   Use the MAE_PhysWorldHit* functions to get more information about the collision.
 *
 * Arguments:
 *   [0]   - Shape
 *   [1]   - Starting point as a vector
 *   [2]   - End point as a vector
 *   [3-4] - Optional group and mask to filter collisions.
 *
 * Returns:
 *   1 on collision, 0 if nothing was hit.
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
