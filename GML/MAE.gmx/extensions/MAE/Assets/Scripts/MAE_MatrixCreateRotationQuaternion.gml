///MAE_MatrixCreateRotationQuaternion(dim,q);

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

switch(argument0) 
{
    case 3:
        var c = 2 * argument1[3] * argument1[3] - 1;
        var s = sqrt(1 - c * c) * sign(argument1[3]);
        
        var mag = sqrt(argument1[0] * argument1[0] + argument1[1] * argument1[1] + argument1[2] * argument1[2]);
        
        if (sign(mag) == 0) {
            var mat;
            
            mat[8] = 1;
            mat[7] = 0;
            mat[6] = 0;
            mat[5] = 0;
            mat[4] = 1;
            mat[3] = 0;
            mat[2] = 0;
            mat[1] = 0;
            mat[0] = 1;
            
            return mat;
        }
        
        argument1[0] /= mag;
        argument1[1] /= mag;
        argument1[2] /= mag;    
    
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
        var c = 2 * argument1[3] * argument1[3] - 1;
        var s = sqrt(1 - c * c) * sign(argument1[3]);
        
        var mag = sqrt(argument1[0] * argument1[0] + argument1[1] * argument1[1] + argument1[2] * argument1[2]);
        
        if (sign(mag) == 0) {
            var mat;
            
            mat[15] = 1;
            mat[14] = 0;
            mat[13] = 0;
            mat[12] = 0;
            mat[11] = 0;
            mat[10] = 1;
            mat[09] = 0;
            mat[08] = 0;
            mat[07] = 0;
            mat[06] = 0;
            mat[05] = 1;
            mat[04] = 0;
            mat[03] = 0;
            mat[02] = 0;
            mat[01] = 0;
            mat[00] = 1;
            
            return mat;
        }
        
        argument1[0] /= mag;
        argument1[1] /= mag;
        argument1[2] /= mag;
        
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
