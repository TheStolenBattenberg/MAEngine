///MAE_MatrixGetMatrix(index);

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

switch (argument0) {
case mat_view:
    return matrix_get(matrix_view);
case mat_projection:
    return matrix_get(matrix_projection);
case mat_world:
    return matrix_get(matrix_world);
case mat_world_view:
    return matrix_multiply(matrix_get(matrix_world), matrix_get(matrix_view));
case mat_world_view_projection:
    return matrix_multiply(matrix_multiply(matrix_get(matrix_world), matrix_get(matrix_view)), matrix_get(matrix_projection));
}

return undefined;
