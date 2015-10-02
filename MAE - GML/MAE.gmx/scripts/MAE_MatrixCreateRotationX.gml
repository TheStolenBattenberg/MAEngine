///MAE_MatrixCreateRotationX(dim, angle);

/**
 * To-do:
 *      Add Description.
 *
 */
switch (argument0) 
{
    case 3:
        var mat;
        
        mat[8] = dcos(argument1);
        mat[7] = -dsin(argument1);
        mat[6] = 0;
        mat[5] = dsin(argument1);
        mat[4] = dcos(argument1);
        mat[3] = 0;
        mat[2] = 0;
        mat[1] = 0;
        mat[0] = 1;    
    return mat;
    
    case 4:
    var mat; 
       
        mat[15] = 1;
        mat[14] = 0;
        mat[13] = 0;
        mat[12] = 0;
        mat[11] = 0;
        mat[10] = dcos(argument1);
        mat[09] = -dsin(argument1);
        mat[08] = 0;
        mat[07] = 0;
        mat[06] = dsin(argument1);
        mat[05] = dcos(argument1);
        mat[04] = 0;
        mat[03] = 0;
        mat[02] = 0;
        mat[01] = 0;
        mat[00] = 1;   
    return mat;
}

return undefined;
