///MAE_PhysConstraintCreateFixed(bodyA,bodyB);

/**
 * Description:
 *   Creates a fixed constraint between 2 physics bodies, based on their current transformations in the world. This locks the 2 bodies together. It better to use a compound shape, if possible, as that will give better results.
 *
 * Arguments:
 *   [1] - BodyA
 *   [2] - BodyB
 *
 * Returns:
 *   Constraint ID
 */

return external_call(global._MAB_ConstraintCreateFixed, argument0, argument1);
