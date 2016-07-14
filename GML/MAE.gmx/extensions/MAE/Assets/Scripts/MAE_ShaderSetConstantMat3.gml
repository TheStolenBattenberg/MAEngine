///MAE_ShaderSetConstantMat3(index,c,mat);

/**
 * Description:
 *   Sets a constant to a mat3 value
 *
 * Arguments:
 *   [1] - Index to the shader created by MAE_ShaderCreate
 *   [2] - Index of the constant
 *   [3] - Value to be set
 *
 * Returns:
 *   0 on Error, 1 on success.
 */

var mat = argument2;

external_call(global._MADX9_MatStackFloat9, mat[0], mat[3], mat[6], mat[1], mat[4], mat[7], mat[2], mat[5], mat[8]);

var r = external_call(global._MAE_ShaderSetConstantMat3, argument0, argument1);

external_call(global._MADX9_MatStackClear);

return r;
