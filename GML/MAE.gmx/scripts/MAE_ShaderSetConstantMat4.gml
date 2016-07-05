///MAE_ShaderSetConstantMat4(index,c,mat)

/**
 * Description:
 *   Sets a constant to a mat4 value
 *
 * Arguments:
 *   [1] - Index to the shader created by MAE_ShaderCreate
 *   [2] - Index of the constant
 *   [3] - Value to be set
 *
 * Returns:
 *   0 on Error, 1 on success.
 */

external_call(global.MADX9_MatStackFloat8, argument2[0], argument2[4], argument2[8],  argument2[12], argument2[1], argument2[5], argument2[9],  argument2[13]);
external_call(global.MADX9_MatStackFloat8, argument2[2], argument2[6], argument2[10], argument2[14], argument2[3], argument2[7], argument2[11], argument2[15]);

var r = external_call(global.__MAE_ShaderSetConstantMat4, argument0, argument1);

external_call(global.MADX9_MatStackClear);

return r;
