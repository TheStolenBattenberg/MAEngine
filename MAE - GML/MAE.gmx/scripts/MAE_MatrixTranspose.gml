///MAE_MatrixTranspose(m);

/**
 * To-do:
 *      Add Description.
 *
 */
switch (array_length_1d(argument0)) {
case 4:
    var m;
    
    m[3] = argument0[3];
    m[2] = argument0[1];
    m[1] = argument0[2];
    m[0] = argument0[0];
    
    return m;
case 9:
    var m;
    
    m[8] = argument0[8];
    m[7] = argument0[5];
    m[6] = argument0[2];
    m[5] = argument0[7];
    m[4] = argument0[4];
    m[3] = argument0[1];
    m[2] = argument0[6];
    m[1] = argument0[3];
    m[0] = argument0[0];
    
    return m;
case 16:
    var m;
    
    m[15] = argument0[15];
    m[14] = argument0[11];
    m[13] = argument0[07];
    m[12] = argument0[03];
    m[11] = argument0[14];
    m[10] = argument0[10];
    m[09] = argument0[06];
    m[08] = argument0[02];
    m[07] = argument0[13];
    m[06] = argument0[09];
    m[05] = argument0[05];
    m[04] = argument0[01];
    m[03] = argument0[12];
    m[02] = argument0[08];
    m[01] = argument0[04];
    m[00] = argument0[00];
    
    return m;
}

return undefined;
