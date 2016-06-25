///MAE_SetRenderState(state,value)

/**
 * Description:
 *   Sets a render state. Sometimes render states aren't applied to gm models.
 *   To fix this you should call MAE_Flush.
 *
 * Arguments:
 *   [1] - State (RENST_*)
 *   [2] - Value depending on the render state
 *
 * Returns:
 *   0 if it is valid pointer, otherwise 1
 */

return external_call(global.MADX9_SetRenderState, argument0, argument1);
