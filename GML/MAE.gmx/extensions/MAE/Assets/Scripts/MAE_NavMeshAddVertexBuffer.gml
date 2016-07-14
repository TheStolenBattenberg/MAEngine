///MAE_NavMeshAddVertexBuffer(index,vertices,triangles,matrix);

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

var matrix = argument3;

external_call(global._MADX9_MatStackFloat8, argument3[0], argument3[4], argument3[8],  argument3[12], argument3[1], argument3[5], argument3[9],  argument3[13]);
external_call(global._MADX9_MatStackFloat8, argument3[2], argument3[6], argument3[10], argument3[14], argument3[3], argument3[7], argument3[11], argument3[15]);

if(argument2 <= 0){
    external_call(global._MA_NavSetVertexBufferSize, buffer_tell(argument1) div 12, 0);
    return external_call(global._MA_NavMeshAddVertexBuffer, argument0, buffer_get_address(argument1), 0);
}

external_call(global._MA_NavSetVertexBufferSize, buffer_tell(argument1) div 12, buffer_tell(argument2) div 12);
return external_call(global._MA_NavMeshAddVertexBuffer, argument0, buffer_get_address(argument1), buffer_get_address(argument2));
