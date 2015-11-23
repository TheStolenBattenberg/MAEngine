///MAE_SetSamplerState(stage,type,value)

/**
 * Description:
 *   Sets a sampler state. Sometimes sampler states aren't applied to gm models.
 *   To fix this you should call MAE_Flush.
 *
 * Arguments:
 *   [1] - Sampler stage
 *   [2] - Sampler state type (SAMP_*)
 *   [3] - Value depending on the state type
 *
 * Returns:
 *   0 if it is valid pointer, otherwise 1
 */

return external_call(global.MADX9_SetSamplerState, argument0, argument1, argument2);
