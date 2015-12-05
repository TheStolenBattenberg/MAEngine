///MAE_PhysBodyCreate(shape, mass, xrot, yrot, zrot, x, y, z)

/**
 * Description:
 *   Creates a rigid body and adds it to the world.
 *
 * Arguments:
 *   [0]   - Shape
 *   [1]   - Mass (0 for static body)
 *   [2-4] - Rotation of the body in euler angles
 *   [5-7] - Position of the body
 *
 * Returns:
 *   Body ID
 */

return external_call(global.MAB_BodyCreate, argument0, argument1, argument2, argument3, argument4, argument5, argument6, argument7);
