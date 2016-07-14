///MAE_MatrixToMat4(m);

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

switch (array_length_1d(argument0)) {
case 4:
    var m;
    
    m[15] = 1;
    m[14] = 0;
    m[13] = 0;
    m[12] = 0;
    m[11] = 0;
    m[10] = 1;
    m[09] = 0;
    m[08] = 0;
    m[07] = 0;
    m[06] = 0;
    m[05] = argument0[3];
    m[04] = argument0[2];
    m[03] = 0;
    m[02] = 0;
    m[01] = argument0[1];
    m[00] = argument0[0];
    
    return m;
case 9:
    var m;
    
    m[15] = 1;
    m[14] = 0;
    m[13] = 0;
    m[12] = 0;
    m[11] = 0;
    m[10] = argument0[8];
    m[09] = argument0[7];
    m[08] = argument0[6];
    m[07] = 0;
    m[06] = argument0[5];
    m[05] = argument0[4];
    m[04] = argument0[3];
    m[03] = 0;
    m[02] = argument0[2];
    m[01] = argument0[1];
    m[00] = argument0[0];
    
    return m;
case 16:
    argument0[0] = argument0[0];
    
    return argument0;
}

return undefined;
