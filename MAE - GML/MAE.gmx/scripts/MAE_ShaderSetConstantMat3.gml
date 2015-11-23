///MAE_ShaderSetConstantMat3(index,shd,c,mat)

/**
 * Description:
 *   Sets a constant to a mat3 value
 *
 * Arguments:
 *   [1] - Index to the shader created by MAE_ShaderCreate
 *   [2] - Shader type (SHD_*)
 *   [3] - Index of the constant
 *   [4] - Value to be set
 *
 * Returns:
 *   0 on Error, 1 on success.
 */

external_call(global.MADX9_MatStackFloat9, argument3[0], argument3[3], argument3[6], argument3[1], argument3[4], argument3[7], argument3[2], argument3[5], argument3[8]);

var r = external_call(global.MADX9_ShaderSetConstantMat3, argument0, argument1, argument2);

external_call(global.MADX9_MatStackClear);

return r;
