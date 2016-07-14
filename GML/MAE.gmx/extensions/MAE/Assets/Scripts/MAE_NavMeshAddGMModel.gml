///MAE_NavMeshAddGMModel(index,filename,matrix);

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

var matrix = argument2;

external_call(global._MADX9_MatStackFloat8, matrix[0], matrix[4], matrix[8],  matrix[12], matrix[1], matrix[5], matrix[9],  matrix[13]);
external_call(global._MADX9_MatStackFloat8, matrix[2], matrix[6], matrix[10], matrix[14], matrix[3], matrix[7], matrix[11], matrix[15]);

return external_call(global._MA_NavMeshAddGMModel, argument0, argument1);
