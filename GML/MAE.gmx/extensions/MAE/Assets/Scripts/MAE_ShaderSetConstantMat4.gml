///MAE_ShaderSetConstantMat4(index,c,mat);

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

var mat = argument2;

external_call(global._MADX9_MatStackFloat8, mat[0], mat[4], mat[8], mat[12], mat[1], mat[5], mat[9], mat[13]);
external_call(global._MADX9_MatStackFloat8, mat[2], mat[6], mat[10], mat[14], mat[3], mat[7], mat[11], mat[15]);

var r = external_call(global._MAE_ShaderSetConstantMat4, argument0, argument1);

external_call(global._MADX9_MatStackClear);

return r;
