#define MAE_QuaternionCreate
var q;

q[3] = argument3;
q[2] = argument2;
q[1] = argument1;
q[0] = argument0;

return q;

#define MAE_QuaternionCreateIdentity
var q;

q[3] = 1;
q[2] = 0;
q[1] = 0;
q[0] = 0;

return q;

#define MAE_QuaternionCreateRotation
var sx = dsin(argument0 / 2);
var cx = dcos(argument0 / 2);
var sy = dsin(argument1 / 2);
var cy = dcos(argument1 / 2);
var sz = dsin(argument2 / 2);
var cz = dcos(argument2 / 2);

var ret;

switch (argument3) {
case EULER_XYZ:
    ret[3] = cx * cy * cz - sx * sy * sz;
    ret[2] = cx * cy * sz + sx * sy * cz;
    ret[1] = cx * sy * cz - sx * cy * sz;
    ret[0] = sx * cy * cz + cx * sy * sz;
    break;
case EULER_YXZ:
    ret[3] = cx * cy * cz + sx * sy * sz;
    ret[2] = cx * cy * sz - sx * sy * cz;
    ret[1] = cx * sy * cz - sx * cy * sz;
    ret[0] = sx * cy * cz + cx * sy * sz;
    break;
case EULER_ZXY:
    ret[3] = cx * cy * cz - sx * sy * sz;
    ret[2] = cx * cy * sz + sx * sy * cz;
    ret[1] = cx * sy * cz + sx * cy * sz;
    ret[0] = sx * cy * cz - cx * sy * sz;
    break;
case EULER_ZYX:
    ret[3] = cx * cy * cz + sx * sy * sz;
    ret[2] = cx * cy * sz - sx * sy * cz;
    ret[1] = cx * sy * cz + sx * cy * sz;
    ret[0] = sx * cy * cz - cx * sy * sz;
    break;
case EULER_YZX:
    ret[3] = cx * cy * cz - sx * sy * sz;
    ret[2] = cx * cy * sz - sx * sy * cz;
    ret[1] = cx * sy * cz + sx * cy * sz;
    ret[0] = sx * cy * cz + cx * sy * sz;
    break;
case EULER_XZY:
    ret[3] = cx * cy * cz + sx * sy * sz;
    ret[2] = cx * cy * sz + sx * sy * cz;
    ret[1] = cx * sy * cz - sx * cy * sz;
    ret[0] = sx * cy * cz - cx * sy * sz;
    break;
default:
    return undefined;
}

return ret;

#define MAE_QuaternionCreateRotationMatrix
var q;

var trace = argument0[0]  + argument0[4] + argument0[8];

if (trace > 0) {
    var s = 0.5 / sqrt(trace + 1);
    
    q[3] = 0.25 / s;
    q[2] = (argument0[1] - argument0[3]) * s;
    q[1] = (argument0[6] - argument0[2]) * s;
    q[0] = (argument0[5] - argument0[7]) * s;
}
else if ((argument0[0] > argument0[4]) && (argument0[0] > argument0[8])) {
    var s = 2 * sqrt(1 + argument0[0] - argument0[4] - argument0[8]);
    
    q[3] = (argument0[5] - argument0[7]) / s;
    q[2] = (argument0[6] + argument0[2]) / s;
    q[1] = (argument0[3] + argument0[1]) / s;
    q[0] = 0.25 * s;
}
else if (argument0[4] > argument0[8]) {
    var s = 2 * sqrt(1 + argument0[4] - argument0[0] - argument0[8]);
    
    q[3] = (argument0[6] - argument0[2]) / s;
    q[2] = (argument0[7] + argument0[5]) / s;
    q[1] = 0.25 * s;
    q[0] = (argument0[3] + argument0[1]) / s;
}
else {
    var s = 2 * sqrt(1 + argument0[8] - argument0[0] - argument0[4]);
    
    q[3] = (argument0[1] - argument0[3]) / s;
    q[2] = 0.25 * s;
    q[1] = (argument0[7] + argument0[5]) / s;
    q[0] = (argument0[6] + argument0[2]) / s;
}

return q;

#define MAE_QuaternionCreateRotationVector
var q;

var l = MAE_VectorMagnitude(argument0);

if (l == 0)
    return MAE_QuaternionCreateIdentity();

q[3] = dcos(argument1 / 2);
q[2] = argument0[2] / l * dsin(argument1 / 2);
q[1] = argument0[1] / l * dsin(argument1 / 2);
q[0] = argument0[0] / l * dsin(argument1 / 2);

return q;

#define MAE_QuaternionDup
argument0[0] = argument0[0];

return argument0;

#define MAE_QuaternionGet
return argument0[argument1];

#define MAE_QuaternionGetRotation
var q = argument0;
var v = argument1;

var x2 = q[0] + q[0];
var y2 = q[1] + q[1];
var z2 = q[2] + q[2];
var xx = q[0] * x2, xy = q[0] * y2, xz = q[0] * z2;
var yy = q[1] * y2, yz = q[1] * z2, zz = q[2] * z2;
var wx = q[3] * x2, wy = q[3] * y2, wz = q[3] * z2;

var m11 = 1 - (yy + zz);
var m12 = xy - wz;
var m13 = xz + wy;
var m21 = xy + wz;
var m22 = 1 - (xx + zz);
var m23 = yz - wx;
var m31 = xz - wy;
var m32 = yz + wx;
var m33 = 1 - (xx + yy);

switch (argument2) {
case EULER_XYZ:
    v[@1] = darcsin(clamp(m13, -1, 1));
    
    if (abs(m13) < 0.99999) {
        v[@0] = darctan2(-m23, m33);
        v[@2] = darctan2(-m12, m11);
    }
    else {
        v[@0] = darctan2(m32, m22);
        v[@2] = 0;
    }
    
    break;
case EULER_YXZ:
    v[@0] = darcsin(-clamp(m23, -1, 1));
    
    if (abs(m23) < 0.99999) {
        v[@1] = darctan2(m13, m33);
        v[@2] = darctan2(m21, m22);
    }
    else {
        v[@1] = darctan2(-m31, m11);
        v[@2] = 0;
    }
    
    break;
case EULER_ZXY:
    v[@0] = darcsin(clamp(m32, -1, 1));
    
    if ( abs( m32 ) < 0.99999 ) {
        v[@1] = darctan2(-m31, m33);
        v[@2] = darctan2(-m12, m22);
    }
    else {
        v[@1] = 0;
        v[@2] = darctan2(m21, m11);
    }
    
    break;
case EULER_ZYX:
    v[@1] = darcsin(-clamp(m31, -1, 1));
    
    if (abs(m31) < 0.99999) {
        v[@0] = darctan2(m32, m33);
        v[@2] = darctan2(m21, m11);
    }
    else {
        v[@0] = 0;
        v[@2] = darctan2(-m12, m22);
    }
    
    break;
case EULER_YZX:
    v[@2] = darcsin(clamp(m21, -1, 1));
    
    if (abs(m21) < 0.99999) {
        v[@0] = darctan2(-m23, m22);
        v[@1] = darctan2(-m31, m11);
    }
    else {
        v[@0] = 0;
        v[@1] = darctan2(m13, m33);
    }
    
    break;
case EULER_XZY:
    v[@2] = darcsin(-clamp(m12, -1, 1));
    
    if (abs(m12) < 0.99999) {
        v[@0] = darctan2(m32, m22);
        v[@1] = darctan2(m13, m11);
    
    }
    else {
        v[@0] = darctan2(-m23, m33);
        v[@1] = 0;
    }
default:
    return undefined;
}

return v;

#define MAE_QuaternionInvert
argument0[@ 0] = -argument0[@ 0];
argument0[@ 1] = -argument0[@ 1];
argument0[@ 2] = -argument0[@ 2];

return argument0;

#define MAE_QuaternionIsQuaternion
return is_array(argument0) && array_length_1d(argument0) == 4;

#define MAE_QuaternionMagnitude
return sqrt(argument0[0] * argument0[0] + argument0[1] * argument0[1] + argument0[2] * argument0[2] + argument0[3] * argument0[3]);

#define MAE_QuaternionMagnitudeSquared
return argument0[0] * argument0[0] + argument0[1] * argument0[1] + argument0[2] * argument0[2] + argument0[3] * argument0[3];

#define MAE_QuaternionMultiply
var q;

q[3] = argument0[3] * argument1[3] - argument0[0] * argument1[0] - argument0[1] * argument1[1] - argument0[2] * argument1[2];
q[2] = argument0[3] * argument1[2] + argument0[2] * argument1[3] + argument0[0] * argument1[1] - argument0[1] * argument1[0];
q[1] = argument0[3] * argument1[1] + argument0[1] * argument1[3] + argument0[2] * argument1[0] - argument0[0] * argument1[2];
q[0] = argument0[3] * argument1[0] + argument0[0] * argument1[3] + argument0[1] * argument1[2] - argument0[2] * argument1[1];

return q;

#define MAE_QuaternionNorm
var l = MAE_QuaternionMagnitude(argument0);

if (l == 0)
    return undefined;

argument0[@ 0] /= l;
argument0[@ 1] /= l;
argument0[@ 2] /= l;
argument0[@ 3] /= l;

return argument0;

#define MAE_QuaternionRotate
return MAE_QuaternionMultiply(argument0, MAE_QuaternionCreateRotation(argument1, argument2, argument3, argument4));

#define MAE_QuaternionRotateMatrix
return MAE_QuaternionMultiply(argument0, MAE_QuaternionCreateRotationMatrix(argument1));

#define MAE_QuaternionRotateVector
return MAE_QuaternionMultiply(argument0, MAE_QuaternionCreateRotationVector(argument1, argument2));

#define MAE_QuaternionSet
argument0[@ argument1] = argument2;

return argument0;

