///MAE_ShaderSetConstantVec4(index,c,vec);

/**
 * Description:
 *   Sets a constant to a vec4 value
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

return external_call(global._MAE_ShaderSetConstantVec4, argument0, argument1, vec[0], vec[1], vec[2], vec[3]);
