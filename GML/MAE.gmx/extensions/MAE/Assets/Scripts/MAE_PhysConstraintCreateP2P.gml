///MAE_PhysConstraintCreateP2P(bodyA,point_A,is_world_space_A,bodyB,point_B,is_world_space_B,disable_collision);

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

var point_A = argument1, point_B = argument4;

return external_call(global._MAB_ConstraintCreateP2P, argument0, point_A[0], point_A[1], point_A[2], argument2, argument3, point_B[0], point_B[1], point_B[2], argument5, argument6);
