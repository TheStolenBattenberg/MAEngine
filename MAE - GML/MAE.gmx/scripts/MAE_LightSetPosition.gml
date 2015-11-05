///MAE_LightSetPosition(Index, X, Y, Z);

/**
 * Description:
 *   Sets the position of a previously created light.
 *
 * Arguments:
 *   [1] - Light Index.
 *   [2] - X Position.
 *   [3] - Y Position.
 *   [4] - Z Position.
 *
 * Returns:
 *   0 on Error, 1 on success. 
 */

return external_call(global.MADX9_LightSetPosition, argument0, argument1, argument2, argument3);
