///MAE_PhysBodyCreate(shape,mass,xrot,yrot,zrot,x,y,z);

/**
 * Description:
 *   Creates a rigid body and adds it to the world.
 *
 * Arguments:
 *   [1] - Shape
 *   [2] - Mass (0 for static body)
 *
 * Returns:
 *   Body ID
 */

return external_call(global._MAB_BodyCreate, argument0, argument1, argument2, argument3, argument4, argument5, argument6, argument7);
