///MAE_ForwardPipelineSetMVP(fp,mat);

/**
 * Description:
 *   
 *
 * Arguments:
 *   [-]
 *
 * Returns:
 *   [-]
 */

var mat = argument1;

external_call(global._MADX9_MatStackFloat8, mat[0], mat[4], mat[8], mat[12], mat[1], mat[5], mat[9], mat[13]);
external_call(global._MADX9_MatStackFloat8, mat[2], mat[6], mat[10], mat[14], mat[3], mat[7], mat[11], mat[15]);

var r = external_call(global._MAE_ForwardPipelineSetMVP, argument0);

external_call(global._MADX9_MatStackClear);

return r;
