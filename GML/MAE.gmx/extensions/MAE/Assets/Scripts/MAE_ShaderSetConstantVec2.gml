///MAE_ShaderSetConstantVec2(index,c,vec);

/**
 * Description:
 *   Sets a constant to a vec2 value
 *
 * Arguments:
 *   [1] - Index to the shader created by MAE_ShaderCreate
 *   [2] - Index of the constant
 *   [3] - Value to be set
 *
 * Returns:
 *   0 on Error, 1 on success.
 */

var vec = argument2;

return external_call(global._MAE_ShaderSetConstantVec2, argument0, argument1, vec[0], vec[1]);
