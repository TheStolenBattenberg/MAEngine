///MAE_PhysConstraintCreateGear(bodyA,bodyB,axis_in_A,axis_in_B,ratio,disable_collision);

/**
 * Description:
 *   Creates a gear constraint between two bodies.
 *
 * Arguments:
 *   [1] - BodyA
 *   [2] - BodyB
 *   [3] - Axis in A, as a vector
 *   [4] - Axis in B, as a vector
 *   [5] - Ratio
 *   [6] - Disable collisions between the 2 bodies?
 *
 * Returns:
 *   Constraint ID
 */

var axisA = argument2;
var axisB = argument3;

return external_call(global._MAB_ConstraintCreateGear, argument0, argument1, axisA[0], axisA[1], axisA[2], axisB[0], axisB[1], axisB[2], argument4, argument5);
