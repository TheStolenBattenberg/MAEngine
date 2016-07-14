///MAE_PhysVertexBufferCreate(size=64);

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

var _size = 64;

if (argument_count > 0)
    _size = argument[0];

return buffer_create(_size, buffer_grow, 4);

