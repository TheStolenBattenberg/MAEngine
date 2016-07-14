///MAE_MatrixCreateLookAt(from_vector,at_vector,up_vector);

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

var zaxis = MAE_VectorNorm(MAE_VectorSubtract(argument1, argument0));
var xaxis = MAE_VectorNorm(MAE_VectorCross(argument2, zaxis));
var yaxis = MAE_VectorCross(zaxis, xaxis);

var mat;
{
    mat[15] = 1;
    mat[14] = -MAE_VectorDot(zaxis, argument0);
    mat[13] = -MAE_VectorDot(yaxis, argument0);
    mat[12] = -MAE_VectorDot(xaxis, argument0);
    mat[11] = 0;
    mat[10] = zaxis[2];
    mat[9]  = yaxis[2];
    mat[8]  = xaxis[2];
    mat[7]  = 0;
    mat[6]  = zaxis[1];
    mat[5]  = yaxis[1];
    mat[4]  = xaxis[1];
    mat[3]  = 0;
    mat[2]  = zaxis[0];
    mat[1]  = yaxis[0];
    mat[0]  = xaxis[0];
}
return mat;
