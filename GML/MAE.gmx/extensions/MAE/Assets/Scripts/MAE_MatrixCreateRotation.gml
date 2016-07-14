///MAE_MatrixCreateRotation(dim,x,y,z,order = EULER_XYZ);

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

if (argument_count > 4)
    _order = argument[4];

switch(argument[0]) {
case 2:
    var s = dsin(argument[3]);
    var c = dcos(argument[3]);
    
    var mat;
    
    mat[3] = c;
    mat[2] = s;
    mat[1] = -s;
    mat[0] = c;
    
    return mat;
case 3:
    var sx = dsin(argument[1]), cx = dcos(argument[1]);
    var sy = dsin(argument[2]), cy = dcos(argument[2]);
    var sz = dsin(argument[3]), cz = dcos(argument[3]);
    
    switch (_order) {
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
