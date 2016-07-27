///MAE_ForwardPipelineSetNormal(fp,mat);

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

external_call(global._MADX9_MatStackFloat9, mat[0], mat[3], mat[6], mat[1], mat[4], mat[7], mat[2], mat[5], mat[8]);

var r = external_call(global._MAE_ForwardPipelineSetNormal, argument0);

external_call(global._MADX9_MatStackClear);

return r;
