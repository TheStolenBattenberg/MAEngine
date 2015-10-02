///MAE_MatrixCreateRotation(dim, x, y, z);

/**
 * To-do:
 *      Add Description.
 *
 */
switch(argument0) 
{
    case 2:
        var mat;    
        mat[3] = dcos(argument3);
        mat[2] = -dsin(argument3);
        mat[1] = dsin(argument3);
        mat[0] = dcos(argument3);  
    return mat;
    
    case 3:
        var sinx = dsin(argument1);
        var cosx = dcos(argument1);
        var siny = dsin(argument2);
        var cosy = dcos(argument2);
        var sinz = dsin(argument3);
        var cosz = dcos(argument3);
    
        var mat;   
        mat[8] = cosx * cosy;
        mat[7] = cosx * siny * sinz + -sinx * cosz;
        mat[6] = cosx * siny * cosz + -sinx * -sinz;
        mat[5] = sinx * cosy;
        mat[4] = sinx * siny * sinz + cosx * cosz;
        mat[3] = sinx * siny * cosz + cosx * -sinz;
        mat[2] = -siny;
        mat[1] = cosy * sinz;
        mat[0] = cosy * cosz;    
    return mat;
    
    case 4:
        var sinx = dsin(argument1);
        var cosx = dcos(argument1);
        var siny = dsin(argument2);
        var cosy = dcos(argument2);
        var sinz = dsin(argument3);
        var cosz = dcos(argument3);
    
        var mat;
    
        mat[15] = 1;
        mat[14] = 0;
        mat[13] = 0;
        mat[12] = 0;
        mat[11] = 0;
        mat[10] = cosx * cosy;
        mat[9]  = cosx * siny * sinz + -sinx * cosz;
        mat[8]  = cosx * siny * cosz + -sinx * -sinz;
        mat[7]  = 0;
        mat[6]  = sinx * cosy;
        mat[5]  = sinx * siny * sinz + cosx * cosz;
        mat[4]  = sinx * siny * cosz + cosx * -sinz;
        mat[3]  = 0;
        mat[2]  = -siny;
        mat[1]  = cosy * sinz;
        mat[0]  = cosy * cosz; 
    return mat;
}
return undefined;
