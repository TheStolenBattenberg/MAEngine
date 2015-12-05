///MAE_PhysConstraintCreateP2P(bodyA, point_A, is_world_space_A, bodyB, point_B, is_world_space_B, disable_collision)
///MAE_PhysConstraintCreateP2P(bodyA, point_A, is_world_space_A)

/**
 * Description:
 *   Creates a point to point constraint between two bodies or between a body and the world.
 *
 * Arguments:
 *   [0] - BodyA
 *   [1] - PointA as a vector
 *   [2] - Is pointA in World space(true), or local space(false)
 *   [3] - BodyB
 *   [4] - PointB as a vector
 *   [5] - Is pointB in World space(true), or local space(false)
 *   [6] - Disable collisions between the 2 bodies?
 *
 * Returns:
 *   Constraint ID
 */

var vecA = argument[1];
if(argument_count == 3) return external_call(global.MAB_ConstraintCreateP2P, argument[0], vecA[0], vecA[1], vecA[2], argument[2], -1, 0, 0, 0, 0, true);
var vecB = argument[4];
return external_call(global.MAB_ConstraintCreateP2P, argument[0], vecA[0], vecA[1], vecA[2], argument[2], argument[3], vecB[0], vecB[1], vecB[2], argument[5], argument[6]);

