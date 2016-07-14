///MAE_MatrixCreateRotationVector(dim,v,angle);

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

switch (argument0) 
{
    case 3:
        var c = dcos(argument2);
        var s = dsin(argument2);
        
        var mat;
        
        mat[8] = argument1[2] * argument1[2] * (1 - c) + c;
        mat[7] = argument1[1] * argument1[2] * (1 - c) + argument1[0] * s;
        mat[6] = argument1[0] * argument1[2] * (1 - c) - argument1[1] * s;
        mat[5] = argument1[1] * argument1[2] * (1 - c) - argument1[0] * s;
        mat[4] = argument1[1] * argument1[1] * (1 - c) + c;
        mat[3] = argument1[1] * argument1[0] * (1 - c) + argument1[2] * s;
        mat[2] = argument1[0] * argument1[2] * (1 - c) + argument1[1] * s;
        mat[1] = argument1[0] * argument1[1] * (1 - c) - argument1[2] * s;
        mat[0] = argument1[0] * argument1[0] * (1 - c) + c;
    return mat;
    
    case 4:
        var c = dcos(argument2);
        var s = dsin(argument2);
        
        var mat;
        
        mat[15] = 1;
        mat[14] = 0;
        mat[13] = 0;
        mat[12] = 0;
        mat[11] = 0;
        mat[10] = argument1[2] * argument1[2] * (1 - c) + c;
        mat[9]  = argument1[1] * argument1[2] * (1 - c) + argument1[0] * s;
        mat[8]  = argument1[0] * argument1[2] * (1 - c) - argument1[1] * s;
        mat[7]  = 0;
        mat[6]  = argument1[1] * argument1[2] * (1 - c) - argument1[0] * s;
        mat[5]  = argument1[1] * argument1[1] * (1 - c) + c;
        mat[4]  = argument1[1] * argument1[0] * (1 - c) + argument1[2] * s;
        mat[3]  = 0;
        mat[2]  = argument1[0] * argument1[2] * (1 - c) + argument1[1] * s;
        mat[1]  = argument1[0] * argument1[1] * (1 - c) - argument1[2] * s;
        mat[0]  = argument1[0] * argument1[0] * (1 - c) + c;
    return mat;
}

return undefined;
