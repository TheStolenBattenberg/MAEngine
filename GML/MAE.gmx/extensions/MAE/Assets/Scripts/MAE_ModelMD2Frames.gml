///MAE_ModelMD2Frames(index);

/**
 * Description:
 *   Returns the total number of frames in a loaded MD2 Model.
 *
 * Arguments:
 *   [1] - MD2 Index.
 *
 * Returns:
 *   0 on Error, 1 on success. 
 */

return external_call(global._MADX9_MD2GetFrames, argument0);
