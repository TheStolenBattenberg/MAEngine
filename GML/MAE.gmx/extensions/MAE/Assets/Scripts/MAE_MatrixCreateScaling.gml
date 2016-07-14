///MAE_MatrixCreateScaling(dim,v);

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
case 2:
    var m;
    
    m[3] = argument1[1];
    m[2] = 0;
    m[1] = 0;
    m[0] = argument1[0];
    
    return m;
case 3:
    var m;
    
    m[8] = argument1[2];
    m[7] = 0;
    m[6] = 0;
    m[5] = 0;
    m[4] = argument1[1];
    m[3] = 0;
    m[2] = 0;
    m[1] = 0;
    m[0] = argument1[0];
    
    return m;
case 4:
    var m;
    
    m[15] = 1;
    m[14] = 0;
    m[13] = 0;
    m[12] = 0;
    m[11] = 0;
    m[10] = argument1[2];
    m[09] = 0;
    m[08] = 0;
    m[07] = 0;
    m[06] = 0;
    m[05] = argument1[1];
    m[04] = 0;
    m[03] = 0;
    m[02] = 0;
    m[01] = 0;
    m[00] = argument1[0];
    
    return m;
}

return undefined;
