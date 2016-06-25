///MAE_ModelMD2Load(model, texture, normals);

/**
 * Description:
 *   Loads MD2 Model and Texture.
 *
 * Arguments:
 *   [1] - MD2 File.
 *   [2] - Texture index.
 *   [3] - Generate normals
 *
 * Returns:
 *   0 on Error, 1 on success. 
 */
 
return external_call(global.MADX9_MD2Load, argument0, argument1, argument2);
