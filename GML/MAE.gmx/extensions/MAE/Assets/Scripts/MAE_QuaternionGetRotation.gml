///MAE_QuaternionGetRotation(q,refvec,order = EULER_XYZ);

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

var _order = EULER_XYZ;

if (argument_count > 2)
    _order = argument[2];

var q = argument[0];
var v = argument[1];

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

switch (_order) {
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
