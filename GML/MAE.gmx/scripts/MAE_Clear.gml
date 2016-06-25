///MAE_Clear(colour,alpha,z,stencil,flags)

/**
 * Description:
 *   Clears render target and/or depth buffer.
 *
 * Arguments:
 *   [1] - Colour to be filled in
 *   [2] - Alpha to be filled in
 *   [3] - Z value to be filled in
 *   [4] - Stencil value to be filled in
 *   [5] - Flags (CLEAR_*)
 *
 * Returns:
 *   0 on Error, 1 on success.
 */

return external_call(global.MADX9_Clear, argument0, argument1, argument2, argument3, argument4);
