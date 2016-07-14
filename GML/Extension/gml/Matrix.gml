#define MAE_MatrixCreate
switch(argument0)
{
    case 2:
        var mat;
        mat[3] = 0;
        mat[2] = 0;
        mat[1] = 0;
        mat[0] = 0;
    return mat;
    
    case 3:
        var mat;
        mat[8] = 0;
        mat[7] = 0;
        mat[6] = 0;
        mat[5] = 0;
        mat[4] = 0;
        mat[3] = 0;
        mat[2] = 0;
        mat[1] = 0;
        mat[0] = 0;
    return mat;
    
    case 4:
        var mat;
        mat[15] = 0;
        mat[14] = 0;
        mat[13] = 0;
        mat[12] = 0;
        mat[11] = 0;
        mat[10] = 0;
        mat[09] = 0;
        mat[08] = 0;
        mat[07] = 0;
        mat[06] = 0;
        mat[05] = 0;
        mat[04] = 0;
        mat[03] = 0;
        mat[02] = 0;
        mat[01] = 0;
        mat[00] = 0;
    return mat;
}
return undefined;

#define MAE_MatrixCreateIdentity
switch(argument0)
{
    case 2:
        var mat;
        mat[3] = 1;
        mat[2] = 0;
        mat[1] = 0;
        mat[0] = 1;
    return mat;
    
    case 3:
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
    
    case 4:
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
return undefined;

#define MAE_MatrixCreateLookAt
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

#define MAE_MatrixCreateNormalMatrix
return MAE_MatrixTranspose(MAE_MatrixInverse(argument0));

#define MAE_MatrixCreateOrtho
var mat;
{
    mat[15] = 1;
    mat[14] = argument4 / (argument4 - argument5);
    mat[13] = (argument1 + argument3) / (argument3 - argument1);
    mat[12] = (argument0 + argument2) / (argument0 - argument2);
    mat[11] = 0;
    mat[10] = 1 / (argument5 - argument4);
    mat[9]  = 0;
    mat[8]  = 0;
    mat[7]  = 0;
    mat[6]  = 0;
    mat[5]  = 2 / (argument1 - argument3);
    mat[4]  = 0;
    mat[3]  = 0;
    mat[2]  = 0;
    mat[1]  = 0;
    mat[0]  = 2 / (argument2 - argument0);
}
return mat;

#define MAE_MatrixCreatePerspective
var yscale = 1 / dtan(argument0 / 2);
var xscale = yscale / argument1;

var mat;
{
    mat[15] = 0;
    mat[14] = -argument2 * argument3 / (argument3 - argument2);
    mat[13] = 0;
    mat[12] = 0;
    mat[11] = 1;
    mat[10] = argument3 / (argument3  - argument2);
    mat[9]  = 0;
    mat[8]  = 0;
    mat[7]  = 0;
    mat[6]  = 0;
    mat[5]  = yscale;
    mat[4]  = 0;
    mat[3]  = 0;
    mat[2]  = 0;
    mat[1]  = 0;
    mat[0]  = xscale;
}
return mat;

#define MAE_MatrixCreateRotation
switch(argument0) {
case 2:
    var s = dsin(argument3);
    var c = dcos(argument3);
    
    var mat;
    
    mat[3] = c;
    mat[2] = s;
    mat[1] = -s;
    mat[0] = c;
    
    return mat;
case 3:
    var sx = dsin(argument1), cx = dcos(argument1);
    var sy = dsin(argument2), cy = dcos(argument2);
    var sz = dsin(argument3), cz = dcos(argument3);
    
    switch (argument4) {
    case EULER_XYZ:
        var mat;
        var ae = cx * cz, af = cx * sz, be = sx * cz, bf = sx * sz;
        
        mat[8] = cx * cy;
        mat[7] = be + af * sy;
        mat[6] = bf - ae * sy;
        mat[5] = - sx * cy;
        mat[4] = ae - bf * sy;
        mat[3] = af + be * sy;
        mat[2] = sy;
        mat[1] = - cy * sz;
        mat[0] = cy * cz;
        
        return mat;
    case EULER_YXZ:
        var mat;
        var ce = cy * cz, cf = cy * sz, de = sy * cz, df = sy * sz;
        
        mat[8] = cx * cy;
        mat[7] = df + ce * sx;
        mat[6] = cf * sx - de;
        mat[5] = - sx;
        mat[4] = cx * cz;
        mat[3] = cx * sz;
        mat[2] = cx * sy;
        mat[1] = de * sx - cf;
        mat[0] = ce + df * sx;
        
        return mat;
    case EULER_ZXY:
        var mat;
        var ce = cy * cz, cf = cy * sz, de = sy * cz, df = sy * sz;
        
        mat[8] = cx * cy;
        mat[7] = sx;
        mat[6] = - cx * sy;
        mat[5] = df - ce * sx;
        mat[4] = cx * cz;
        mat[3] = cf + de * sx;
        mat[2] = de + cf * sx;
        mat[1] = - cx * sz;
        mat[0] = ce - df * sx;
        
        return mat;
    case EULER_ZYX:
        var mat;
        var ae = cx * cz, af = cx * sz, be = sx * cz, bf = sx * sz;
        
        mat[8] = cx * cy;
        mat[7] = sx * cy;
        mat[6] = - sy;
        mat[5] = af * sy - be;
        mat[4] = bf * sy + ae;
        mat[3] = cy * sz;
        mat[2] = ae * sy + bf;
        mat[1] = be * sy - af;
        mat[0] = cy * cz;
        
        return mat;
    case EULER_YZX:
        var mat;
        var ac = cx * cy, ad = cx * sy, bc = sx * cy, bd = sx * sy;
        
        mat[8] = ac - bd * sz;
        mat[7] = ad * sz + bc;
        mat[6] = - sy * cz;
        mat[5] = - sx * cz;
        mat[4] = cx * cz;
        mat[3] = sz;
        mat[2] = bc * sz + ad;
        mat[1] = bd - ac * sz;
        mat[0] = cy * cz;
        
        return mat;
    case EULER_XZY:
        var mat;
        var ac = cx * cy, ad = cx * sy, bc = sx * cy, bd = sx * sy;
        
        mat[8] = bd * sz + ac;
        mat[7] = sx * cz;
        mat[6] = bc * sz - ad;
        mat[5] = ad * sz - bc;
        mat[4] = cx * cz;
        mat[3] = ac * sz + bd;
        mat[2] = sy * cz;
        mat[1] = - sz;
        mat[0] = cy * cz;
        
        return mat;
    }
    break;
case 4:
    var sx = dsin(argument[1]), cx = dcos(argument[1]);
    var sy = dsin(argument[2]), cy = dcos(argument[2]);
    var sz = dsin(argument[3]), cz = dcos(argument[3]);
    
    var mat;
    
    mat[15] = 1;
    mat[14] = 0;
    mat[13] = 0;
    mat[12] = 0;
    mat[11] = 0;
    mat[7]  = 0;
    mat[3]  = 0;
    
    switch (order) {
    case EULER_XYZ:
        var mat;
        var ae = cx * cz, af = cx * sz, be = sx * cz, bf = sx * sz;
        
        mat[10] = cx * cy;
        mat[9] = be + af * sy;
        mat[8] = bf - ae * sy;
        mat[6] = - sx * cy;
        mat[5] = ae - bf * sy;
        mat[4] = af + be * sy;
        mat[2] = sy;
        mat[1] = - cy * sz;
        mat[0] = cy * cz;
        
        return mat;
    case EULER_YXZ:
        var mat;
        var ce = cy * cz, cf = cy * sz, de = sy * cz, df = sy * sz;
        
        mat[10] = cx * cy;
        mat[9] = df + ce * sx;
        mat[8] = cf * sx - de;
        mat[6] = - sx;
        mat[5] = cx * cz;
        mat[4] = cx * sz;
        mat[2] = cx * sy;
        mat[1] = de * sx - cf;
        mat[0] = ce + df * sx;
        
        return mat;
    case EULER_ZXY:
        var mat;
        var ce = cy * cz, cf = cy * sz, de = sy * cz, df = sy * sz;
        
        mat[10] = cx * cy;
        mat[9] = sx;
        mat[8] = - cx * sy;
        mat[6] = df - ce * sx;
        mat[5] = cx * cz;
        mat[4] = cf + de * sx;
        mat[2] = de + cf * sx;
        mat[1] = - cx * sz;
        mat[0] = ce - df * sx;
        
        return mat;
    case EULER_ZYX:
        var mat;
        var ae = cx * cz, af = cx * sz, be = sx * cz, bf = sx * sz;
        
        mat[10] = cx * cy;
        mat[9] = sx * cy;
        mat[8] = - sy;
        mat[6] = af * sy - be;
        mat[5] = bf * sy + ae;
        mat[4] = cy * sz;
        mat[2] = ae * sy + bf;
        mat[1] = be * sy - af;
        mat[0] = cy * cz;
        
        return mat;
    case EULER_YZX:
        var mat;
        var ac = cx * cy, ad = cx * sy, bc = sx * cy, bd = sx * sy;
        
        mat[10] = ac - bd * sz;
        mat[9] = ad * sz + bc;
        mat[8] = - sy * cz;
        mat[6] = - sx * cz;
        mat[5] = cx * cz;
        mat[4] = sz;
        mat[2] = bc * sz + ad;
        mat[1] = bd - ac * sz;
        mat[0] = cy * cz;
        
        return mat;
    case EULER_XZY:
        var mat;
        var ac = cx * cy, ad = cx * sy, bc = sx * cy, bd = sx * sy;
        
        mat[10] = bd * sz + ac;
        mat[9] = sx * cz;
        mat[8] = bc * sz - ad;
        mat[6] = ad * sz - bc;
        mat[5] = cx * cz;
        mat[4] = ac * sz + bd;
        mat[2] = sy * cz;
        mat[1] = - sz;
        mat[0] = cy * cz;
        
        return mat;
    }
    break;
}

return undefined;

#define MAE_MatrixCreateRotationQuaternion
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

#define MAE_MatrixCreateRotationVector
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

#define MAE_MatrixCreateRotationX
var c = dcos(argument1), s = dsin(argument1);

switch (argument0)  {
case 3:
    var mat;
    
    mat[8] = c;
    mat[7] = s;
    mat[6] = 0;
    mat[5] = -s;
    mat[4] = c;
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
    mat[10] = 0;
    mat[09] = s;
    mat[09] = c;
    mat[08] = 0;
    mat[07] = 0;
    mat[06] = -s;
    mat[05] = c;
    mat[04] = 0;
    mat[03] = 0;
    mat[02] = 0;
    mat[01] = 0;
    mat[00] = 1;
    
    return mat;
}

return undefined;

#define MAE_MatrixCreateRotationY
var c = dcos(argument1), s = dsin(argument1);

switch (argument0) {
case 3:
    var mat;
    
    mat[8] = c;
    mat[7] = 0;
    mat[6] = -s;
    mat[5] = 0;
    mat[4] = 1;
    mat[3] = 0;
    mat[2] = s;
    mat[1] = 0;
    mat[0] = c;
    
    return mat;
case 4:
    var mat;
    
    mat[15] = 1;
    mat[14] = 0;
    mat[13] = 0;
    mat[12] = 0;
    mat[11] = 0;
    mat[10] = c;
    mat[09] = 0;
    mat[08] = -s;
    mat[07] = 0;
    mat[06] = 0;
    mat[05] = 1;
    mat[04] = 0;
    mat[03] = 0;
    mat[02] = s;
    mat[01] = 0;
    mat[00] = c;
    
    return mat;
}

return undefined;

#define MAE_MatrixCreateRotationZ
var c = dcos(argument1), s = dsin(argument1);

switch (argument0) {
case 2:
    var mat;
    
    mat[3] = c;
    mat[2] = s;
    mat[1] = -s;
    mat[0] = c;
    
    return mat;
case 3:
    var mat;
    
    mat[8] = 1;
    mat[7] = 0;
    mat[6] = 0;
    mat[5] = 0;
    mat[4] = c;
    mat[3] = s;
    mat[2] = 0;
    mat[1] = -s;
    mat[0] = c;
    
    return mat;
case 4:
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
    mat[05] = c;
    mat[04] = s;
    mat[03] = 0;
    mat[02] = 0;
    mat[01] = -s;
    mat[00] = c;
    
    return mat;
}

return undefined;

#define MAE_MatrixCreateScaling
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

#define MAE_MatrixCreateTranslation
var m;

m[15] = 1;
m[14] = argument0[2];
m[13] = argument0[1];
m[12] = argument0[0];
m[11] = 0;
m[10] = 1;
m[09] = 0;
m[08] = 0;
m[07] = 0;
m[06] = 0;
m[05] = 1;
m[04] = 0;
m[03] = 0;
m[02] = 0;
m[01] = 0;
m[00] = 1;

return m;

#define MAE_MatrixDet
switch (array_length_1d(argument0)) {
case 4:
    return argument0[0] * argument[3] - argument0[2] * argument0[1];
case 9:
    return argument0[0] * argument0[4] * argument0[8] + argument0[3] * argument0[7] * argument0[2] +
           argument0[6] * argument0[1] * argument0[5] - argument0[6] * argument0[4] * argument0[2] -
           argument0[3] * argument0[1] * argument0[8] - argument0[0] * argument0[7] * argument0[5];
case 16:
    return argument0[00] * argument0[05] * argument0[10] * argument0[15] + argument0[04] * argument0[09] * argument0[14] * argument0[03] +
           argument0[08] * argument0[13] * argument0[02] * argument0[07] + argument0[12] * argument0[01] * argument0[06] * argument0[11] -
           argument0[12] * argument0[09] * argument0[06] * argument0[03] - argument0[08] * argument0[05] * argument0[02] * argument0[15] -
           argument0[04] * argument0[01] * argument0[14] * argument0[11] - argument0[00] * argument0[13] * argument0[10] * argument0[07];
}

return undefined;

#define MAE_MatrixDivide
switch (array_length_1d(argument0)) {
case 4:
    argument0[@ 0] /= argument1;
    argument0[@ 1] /= argument1;
    argument0[@ 2] /= argument1;
    argument0[@ 3] /= argument1;
    
    return argument0;
case 9:
    argument0[@ 0] /= argument1;
    argument0[@ 1] /= argument1;
    argument0[@ 2] /= argument1;
    argument0[@ 3] /= argument1;
    argument0[@ 4] /= argument1;
    argument0[@ 5] /= argument1;
    argument0[@ 6] /= argument1;
    argument0[@ 7] /= argument1;
    argument0[@ 8] /= argument1;
    
    return argument0;
case 16:
    argument0[@ 00] /= argument1;
    argument0[@ 01] /= argument1;
    argument0[@ 02] /= argument1;
    argument0[@ 03] /= argument1;
    argument0[@ 04] /= argument1;
    argument0[@ 05] /= argument1;
    argument0[@ 06] /= argument1;
    argument0[@ 07] /= argument1;
    argument0[@ 08] /= argument1;
    argument0[@ 09] /= argument1;
    argument0[@ 10] /= argument1;
    argument0[@ 11] /= argument1;
    argument0[@ 12] /= argument1;
    argument0[@ 13] /= argument1;
    argument0[@ 14] /= argument1;
    argument0[@ 15] /= argument1;
    
    return argument0;
}

return undefined;

#define MAE_MatrixDup
argument0[0] = argument0[0];

return argument0;

#define MAE_MatrixGet
return argument0[argument2 + argument1 * MAE_MatrixGetDimension(argument0)];

#define MAE_MatrixGetDimension
switch (array_length_1d(argument0)) {
case 4:
    return 2;
case 9:
    return 3;
case 16:
    return 4;
}

return undefined;

#define MAE_MatrixGetMatrix
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

#define MAE_MatrixInverse
switch (array_length_1d(argument0)) {
case 4:
    var mat;
    
    mat[3] =  argument0[0];
    mat[2] = -argument0[2];
    mat[1] = -argument0[1];
    mat[0] =  argument0[3];
    
    var det = argument0[0] * argument0[3] - argument0[2] * argument0[1];
    
    if (sign(det) == 0)
        return undefined;
    
    MAE_MatrixDivide(mat, det);
    
    return mat;
case 9:
    var mat;
    
    mat[8] = argument0[4] * argument0[0] - argument0[3] * argument0[1];
    mat[7] = argument0[1] * argument0[6] - argument0[0] * argument0[7];
    mat[6] = argument0[3] * argument0[7] - argument0[6] * argument0[4];
    mat[5] = argument0[3] * argument0[2] - argument0[5] * argument0[0];
    mat[4] = argument0[0] * argument0[8] - argument0[2] * argument0[6];
    mat[3] = argument0[5] * argument0[6] - argument0[8] * argument0[3];
    mat[2] = argument0[5] * argument0[1] - argument0[4] * argument0[2];
    mat[1] = argument0[2] * argument0[7] - argument0[1] * argument0[8];
    mat[0] = argument0[4] * argument0[8] - argument0[7] * argument0[5];
    
    var det = argument0[0] * (argument0[4] * argument0[8] - argument0[7] * argument0[5]) -
              argument0[3] * (argument0[1] * argument0[8] - argument0[7] * argument0[2]) +
              argument0[6] * (argument0[1] * argument0[5] - argument0[4] * argument0[2])
    
    if (sign(det) == 0)
        return undefined;
    
    MAE_MatrixDivide(mat, det);
    
    return mat;
case 16:
    var val00 = argument0[10] * argument0[15] - argument0[14] * argument0[11];
    var val01 = argument0[09] * argument0[15] - argument0[13] * argument0[11];
    var val02 = argument0[09] * argument0[14] - argument0[13] * argument0[10];
    var val03 = argument0[08] * argument0[15] - argument0[12] * argument0[11];
    var val04 = argument0[08] * argument0[14] - argument0[12] * argument0[10];
    var val05 = argument0[08] * argument0[13] - argument0[12] * argument0[09];
    var val06 = argument0[06] * argument0[15] - argument0[14] * argument0[07];
    var val07 = argument0[05] * argument0[15] - argument0[13] * argument0[07];
    var val08 = argument0[05] * argument0[14] - argument0[13] * argument0[06];
    var val09 = argument0[04] * argument0[15] - argument0[12] * argument0[07];
    var val10 = argument0[04] * argument0[14] - argument0[12] * argument0[06];
    var val11 = argument0[05] * argument0[15] - argument0[13] * argument0[07];
    var val12 = argument0[04] * argument0[13] - argument0[12] * argument0[05];
    var val13 = argument0[06] * argument0[11] - argument0[10] * argument0[07];
    var val14 = argument0[05] * argument0[11] - argument0[09] * argument0[07];
    var val15 = argument0[05] * argument0[10] - argument0[09] * argument0[06];
    var val16 = argument0[04] * argument0[11] - argument0[08] * argument0[07];
    var val17 = argument0[04] * argument0[10] - argument0[08] * argument0[06];
    var val18 = argument0[04] * argument0[09] - argument0[08] * argument0[05];
    
    var mat;
    
    mat[15] =  argument0[0] * val15 - argument0[1] * val17 + argument0[2] * val18;
    mat[14] = -argument0[0] * val08 + argument0[1] * val10 - argument0[2] * val12;
    mat[13] =  argument0[0] * val02 - argument0[1] * val04 + argument0[2] * val05;
    mat[12] = -argument0[4] * val02 + argument0[5] * val04 - argument0[6] * val05;
    mat[11] = -argument0[0] * val14 + argument0[1] * val16 - argument0[3] * val18;
    mat[10] =  argument0[0] * val11 - argument0[1] * val09 + argument0[3] * val12;
    mat[09] = -argument0[0] * val01 + argument0[1] * val03 - argument0[3] * val05;
    mat[08] =  argument0[4] * val01 - argument0[5] * val03 + argument0[7] * val05;
    mat[07] =  argument0[0] * val13 - argument0[2] * val16 + argument0[3] * val17;
    mat[06] = -argument0[0] * val06 + argument0[2] * val09 - argument0[3] * val10;
    mat[05] =  argument0[0] * val00 - argument0[2] * val03 + argument0[3] * val04;
    mat[04] = -argument0[4] * val00 + argument0[6] * val03 - argument0[7] * val04;
    mat[03] = -argument0[1] * val13 + argument0[2] * val14 - argument0[3] * val15;
    mat[02] =  argument0[1] * val06 - argument0[2] * val07 + argument0[3] * val08;
    mat[01] = -argument0[1] * val00 + argument0[2] * val01 - argument0[3] * val02;
    mat[00] =  argument0[5] * val00 - argument0[6] * val01 + argument0[7] * val02;
    
    var det = argument0[0] * mat[0] + argument0[1] * mat[4] + argument0[2] * mat[8] + argument0[3] * mat[12];
    
    if (sign(det) == 0)
        return undefined;
    
    MAE_MatrixDivide(mat, det);
    
    return mat;
}

return undefined;

#define MAE_MatrixMultiply
switch (array_length_1d(argument0)) {
case 4:
    argument0[@ 0] *= argument1;
    argument0[@ 1] *= argument1;
    argument0[@ 2] *= argument1;
    argument0[@ 3] *= argument1;
    
    return argument0;
case 9:
    argument0[@ 0] *= argument1;
    argument0[@ 1] *= argument1;
    argument0[@ 2] *= argument1;
    argument0[@ 3] *= argument1;
    argument0[@ 4] *= argument1;
    argument0[@ 5] *= argument1;
    argument0[@ 6] *= argument1;
    argument0[@ 7] *= argument1;
    argument0[@ 8] *= argument1;
    
    return argument0;
case 16:
    argument0[@ 00] *= argument1;
    argument0[@ 01] *= argument1;
    argument0[@ 02] *= argument1;
    argument0[@ 03] *= argument1;
    argument0[@ 04] *= argument1;
    argument0[@ 05] *= argument1;
    argument0[@ 06] *= argument1;
    argument0[@ 07] *= argument1;
    argument0[@ 08] *= argument1;
    argument0[@ 09] *= argument1;
    argument0[@ 10] *= argument1;
    argument0[@ 11] *= argument1;
    argument0[@ 12] *= argument1;
    argument0[@ 13] *= argument1;
    argument0[@ 14] *= argument1;
    argument0[@ 15] *= argument1;
    
    return argument0;
}

return undefined;

#define MAE_MatrixMultiplyMatrix
switch (array_length_1d(argument0)) {
case 4:
    var mat;
    
    mat[3] = argument0[2] * argument1[1] + argument0[3] * argument1[3];
    mat[2] = argument0[2] * argument1[0] + argument0[3] * argument1[2];
    mat[1] = argument0[0] * argument1[1] + argument0[1] * argument1[3];
    mat[0] = argument0[0] * argument1[0] + argument0[1] * argument1[2];
    
    return mat;
case 9:
    var mat;
    
    mat[8] = argument0[6] * argument1[2] + argument0[7] * argument1[5] + argument0[8] * argument1[8];
    mat[7] = argument0[6] * argument1[1] + argument0[7] * argument1[4] + argument0[8] * argument1[7];
    mat[6] = argument0[6] * argument1[0] + argument0[7] * argument1[3] + argument0[8] * argument1[6];
    mat[5] = argument0[3] * argument1[2] + argument0[4] * argument1[5] + argument0[5] * argument1[8];
    mat[4] = argument0[3] * argument1[1] + argument0[4] * argument1[4] + argument0[5] * argument1[7];
    mat[3] = argument0[3] * argument1[0] + argument0[4] * argument1[3] + argument0[5] * argument1[6];
    mat[2] = argument0[0] * argument1[2] + argument0[1] * argument1[5] + argument0[2] * argument1[8];
    mat[1] = argument0[0] * argument1[1] + argument0[1] * argument1[4] + argument0[2] * argument1[7];
    mat[0] = argument0[0] * argument1[0] + argument0[1] * argument1[3] + argument0[2] * argument1[6];
    
    return mat;
case 16:
    return matrix_multiply(argument0, argument1);
}

return undefined;

#define MAE_MatrixRotate
return MAE_MatrixMultiplyMatrix(argument[0], MAE_MatrixCreateRotation(MAE_MatrixGetDimension(argument0), argument1, argument2, argument3, argument4));

#define MAE_MatrixRotateQuaternion
return MAE_MatrixMultiplyMatrix(argument0, MAE_MatrixCreateRotationQuaternion(MAE_MatrixGetDimension(argument0), argument1));

#define MAE_MatrixRotateVector
return MAE_MatrixMultiplyMatrix(argument0, MAE_MatrixCreateRotationVector(MAE_MatrixGetDimension(argument0), argument1, argument2));

#define MAE_MatrixRotateX
return MAE_MatrixMultiplyMatrix(argument1, MAE_MatrixCreateRotationX(MAE_MatrixGetDimension(argument0), argument1));

#define MAE_MatrixRotateY
return MAE_MatrixMultiplyMatrix(argument1, MAE_MatrixCreateRotationY(MAE_MatrixGetDimension(argument0), argument1));

#define MAE_MatrixRotateZ
return MAE_MatrixMultiplyMatrix(argument1, MAE_MatrixCreateRotationZ(MAE_MatrixGetDimension(argument0), argument1));

#define MAE_MatrixScale
switch (array_length_1d(argument0)) {
case 4:
    argument0[0] *= argument1[0];
    argument0[1] *= argument1[1];
    argument0[2] *= argument1[0];
    argument0[3] *= argument1[1];
    
    return argument0;
case 9:
    argument0[0] *= argument1[0];
    argument0[1] *= argument1[1];
    argument0[2] *= argument1[2];
    argument0[3] *= argument1[0];
    argument0[4] *= argument1[1];
    argument0[5] *= argument1[2];
    argument0[6] *= argument1[0];
    argument0[7] *= argument1[1];
    argument0[8] *= argument1[2];
    
    return argument0;
case 16:
    argument0[00] *= argument1[0];
    argument0[01] *= argument1[1];
    argument0[02] *= argument1[2];
    argument0[04] *= argument1[0];
    argument0[05] *= argument1[1];
    argument0[06] *= argument1[2];
    argument0[08] *= argument1[0];
    argument0[09] *= argument1[1];
    argument0[10] *= argument1[2];
    argument0[12] *= argument1[0];
    argument0[13] *= argument1[1];
    argument0[14] *= argument1[2];
    
    return argument0;
}

return undefined;

#define MAE_MatrixSet
argument0[@ argument2 + argument1 * MAE_MatrixGetDimension(argument0)] = argument3;
return argument0;

#define MAE_MatrixTranslate
var m14 = argument0[3];
var m24 = argument0[7];
var m34 = argument0[11];
var m44 = argument0[15];

if (sign(m14) != 0 || sign(m24) != 0 || sign(m34) != 0) {
    argument0[00] += m14 * argument1[0];
    argument0[01] += m14 * argument1[1];
    argument0[02] += m14 * argument1[2];
    argument0[04] += m24 * argument1[0];
    argument0[05] += m24 * argument1[1];
    argument0[06] += m24 * argument1[2];
    argument0[08] += m34 * argument1[0];
    argument0[09] += m34 * argument1[1];
    argument0[10] += m34 * argument1[2];
}

argument0[12] += m44 * argument1[0];
argument0[13] += m44 * argument1[1];
argument0[14] += m44 * argument1[2];

return argument0;

#define MAE_MatrixTranspose
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

#define MAE_MatrixToMat2
switch (array_length_1d(argument0)) {
case 4:
    argument0[0] = argument0[0];
    
    return argument0;
case 9:
    var m;
    
    m[3] = argument0[4];
    m[2] = argument0[3];
    m[1] = argument0[1];
    m[0] = argument0[0];
    
    return m;
case 16:
    var m;
    
    m[3] = argument0[5];
    m[2] = argument0[4];
    m[1] = argument0[1];
    m[0] = argument0[0];
    
    return m;
}

return undefined;

#define MAE_MatrixToMat3
switch (array_length_1d(argument0)) {
case 4:
    var m;
    
    m[8] = 1;
    m[7] = 0;
    m[6] = 0;
    m[5] = 0;
    m[4] = argument0[3];
    m[3] = argument0[2];
    m[2] = 0;
    m[1] = argument0[1];
    m[0] = argument0[0];
    
    return m;
case 9:
    argument0[0] = argument0[0];
    
    return argument0;
case 16:
    var m;
    
    m[8] = argument0[10];
    m[7] = argument0[9];
    m[6] = argument0[8];
    m[5] = argument0[6];
    m[4] = argument0[5];
    m[3] = argument0[4];
    m[2] = argument0[2];
    m[1] = argument0[1];
    m[0] = argument0[0];
    
    return m;
}

return undefined;

#define MAE_MatrixToMat4
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

#define MAE_MatrixIsMat2
return is_array(argument0) && array_length_1d(argument0) == 4;

#define MAE_MatrixIsMat3
return is_array(argument0) && array_length_1d(argument0) == 9;

#define MAE_MatrixIsMat4
return is_array(argument0) && array_length_1d(argument0) == 16;

