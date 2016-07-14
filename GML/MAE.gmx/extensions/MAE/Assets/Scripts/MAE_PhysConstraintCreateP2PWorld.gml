///MAE_PhysConstraintCreateP2PWorld(body,point,is_world_space);

/**
 * Description:
 *   Creates a point to point constraint between two bodies or between a body and the world.
 *
 * Arguments:
 *   [1] - BodyA
 *   [2] - PointA as a vector
 *   [3] - Is pointA in World space(true), or local space(false)
 *   [4] - BodyB
 *   [5] - PointB as a vector
 *   [6] - Is pointB in World space(true), or local space(false)
 *   [7] - Disable collisions between the 2 bodies?
 *
 * Returns:
 *   Constraint ID
 */

var point = argument1;

return external_call(global._MAB_ConstraintCreateP2P, argument0, point[0], point[1], point[2], argument2, -1, 0, 0, 0, 0, true);
