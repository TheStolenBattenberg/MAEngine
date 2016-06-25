///MAE_PhysConstraintCreateGear(bodyA, bodyB, axis_in_A, axis_in_B, ratio, disable_collision)

/**
 * Description:
 *   Creates a gear constraint between two bodies.
 *
 * Arguments:
 *   [0] - BodyA
 *   [1] - BodyB
 *   [2] - Axis in A, as a vector
 *   [3] - Axis in B, as a vector
 *   [4] - Ratio
 *   [5] - Disable collisions between the 2 bodies?
 *
 * Returns:
 *   Constraint ID
 */

var axisA = argument2;
var axisB = argument3;
return external_call(global.MAB_ConstraintCreateGear, argument0, argument1, axisA[0], axisA[1], axisA[2], axisB[0], axisB[1], axisB[2], argument4, argument5);

