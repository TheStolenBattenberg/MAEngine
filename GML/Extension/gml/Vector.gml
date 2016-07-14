#define MAE_VectorCreate
switch (argument_count) {
case 2:
    var v;
    
    v[1] = argument[1];
    v[0] = argument[0];
    
    return v;
case 3:
    var v;
    
    v[2] = argument[2];
    v[1] = argument[1];
    v[0] = argument[0];
    
    return v;
case 4:
    var v;
    
    v[3] = argument[3];
    v[2] = argument[2];
    v[1] = argument[1];
    v[0] = argument[0];
    
    return v;
}

return undefined;

#define MAE_VectorCreateAngle2D
var v;

v[1] = -dsin(argument0);
v[0] = dcos(argument0);

return v;

#define MAE_VectorCreateAngle3D
var v;

v[2] = dsin(argument1);
v[1] = -dsin(argument0) * dcos(argument1);
v[0] = dcos(argument0) * dcos(argument1);

return v;

#define MAE_VectorIsVec2
return is_array(argument0) && array_length_1d(argument0) == 2;

#define MAE_VectorIsVec3
return is_array(argument0) && array_length_1d(argument0) == 3;

#define MAE_VectorIsVec4
return is_array(argument0) && array_length_1d(argument0) == 4;

#define MAE_ToVec2
var v;

v[1] = undefined;

var ind = 0;

for (var i = 0; i < argument_count; ++i) {
    if (is_array(argument[i])) {
        var a = argument[i];
        
        for (var j = 0; j < array_length_1d(a); ++j) {
            v[ind++] = a[j];
            
            if (ind >= 2)
                return v;
        }
    }
    else {
        v[ind++] = argument[i];
        
        if (ind >= 2)
            return v;
    }
}

if (ind == 1)
    v[ind++] = v[0];

if (ind < 2)
    return undefined;

return v;

#define MAE_ToVec3
var v;

v[2] = undefined;

var ind = 0;

for (var i = 0; i < argument_count; ++i) {
    if (is_array(argument[i])) {
        var a = argument[i];
        
        for (var j = 0; j < array_length_1d(a); ++j) {
            v[ind++] = a[j];
            
            if (ind >= 3)
                return v;
        }
    }
    else {
        v[ind++] = argument[i];
        
        if (ind >= 3)
            return v;
    }
}

if (ind == 1) {
    v[ind++] = v[0];
    v[ind++] = v[0];
}

if (ind < 3)
    return undefined;

return v;

#define MAE_ToVec4
var v;

v[3] = undefined;

var ind = 0;

for (var i = 0; i < argument_count; ++i) {
    if (is_array(argument[i])) {
        var a = argument[i];
        
        for (var j = 0; j < array_length_1d(a); ++j) {
            v[ind++] = a[j];
            
            if (ind >= 4)
                return v;
        }
    }
    else {
        v[ind++] = argument[i];
        
        if (ind >= 4)
            return v;
    }
}

if (ind == 1) {
    v[ind++] = v[0];
    v[ind++] = v[0];
    v[ind++] = v[0];
}

if (ind == 2) {
    v[ind++] = v[0];
    v[ind++] = v[1];
}

if (ind < 4)
    return undefined;

return v;

#define MAE_VectorAdd
switch (array_length_1d(argument0)) {
case 2:
    argument0[0] += argument1[0];
    argument0[1] += argument1[1];
    
    return argument0;
case 3:
    argument0[0] += argument1[0];
    argument0[1] += argument1[1];
    argument0[2] += argument1[2];
    
    return argument0;
case 4:
    argument0[0] += argument1[0];
    argument0[1] += argument1[1];
    argument0[2] += argument1[2];
    argument0[3] += argument1[3];
    
    return argument0;
}

return undefined;

#define MAE_VectorSubtract
switch (array_length_1d(argument0)) {
case 2:
    argument0[0] -= argument1[0];
    argument0[1] -= argument1[1];
    
    return argument0;
case 3:
    argument0[0] -= argument1[0];
    argument0[1] -= argument1[1];
    argument0[2] -= argument1[2];
    
    return argument0;
case 4:
    argument0[0] -= argument1[0];
    argument0[1] -= argument1[1];
    argument0[2] -= argument1[2];
    argument0[3] -= argument1[3];
    
    return argument0;
}

return undefined;

#define MAE_VectorDivide
switch (array_length_1d(argument0)) {
case 2:
    argument0[@ 0] /= argument1;
    argument0[@ 1] /= argument1;
    
    return argument0;
case 3:
    argument0[@ 0] /= argument1;
    argument0[@ 1] /= argument1;
    argument0[@ 2] /= argument1;
    
    return argument0;
case 4:
    argument0[@ 0] /= argument1;
    argument0[@ 1] /= argument1;
    argument0[@ 2] /= argument1;
    argument0[@ 3] /= argument1;
    
    return argument0;
}

return undefined;

#define MAE_VectorMultiply
switch (array_length_1d(argument0)) {
case 2:
    argument0[@ 0] *= argument1;
    argument0[@ 1] *= argument1;
    
    return argument0;
case 3:
    argument0[@ 0] *= argument1;
    argument0[@ 1] *= argument1;
    argument0[@ 2] *= argument1;
    
    return argument0;
case 4:
    argument0[@ 0] *= argument1;
    argument0[@ 1] *= argument1;
    argument0[@ 2] *= argument1;
    argument0[@ 3] *= argument1;
    
    return argument0;
}

return undefined;

#define MAE_VectorCross
var v;

v[2] = argument0[0] * argument1[1] - argument0[1] * argument1[0];
v[1] = argument0[2] * argument1[0] - argument0[0] * argument1[2];
v[0] = argument0[1] * argument1[2] - argument0[2] * argument1[1];

return v;

#define MAE_VectorDistance
return MAE_VectorMagnitude(MAE_VectorSubtract(argument0, argument1));

#define MAE_VectorDot
switch (array_length_1d(argument0)) {
case 2:
    return argument0[0] * argument1[0] + argument0[1] * argument1[1];
case 3:
    return argument0[0] * argument1[0] + argument0[1] * argument1[1] + argument0[2] * argument1[2];
case 4:
    return argument0[0] * argument1[0] + argument0[1] * argument1[1] + argument0[2] * argument1[2] + argument0[3] * argument1[3];
}

return undefined;

#define MAE_VectorDup
argument0[0] = argument0[0];

return argument0;

#define MAE_VectorGet
return argument0[argument1];

#define MAE_VectorMagnitude
switch (array_length_1d(argument0)) {
case 2:
    return sqrt(argument0[0] * argument0[0] + argument0[1] * argument0[1]);
case 3:
    return sqrt(argument0[0] * argument0[0] + argument0[1] * argument0[1] + argument0[2] * argument0[2]);
case 4:
    return sqrt(argument0[0] * argument0[0] + argument0[1] * argument0[1] + argument0[2] * argument0[2] + argument0[3] * argument0[3]);
}

return undefined;

#define MAE_VectorMagnitudeSquared
switch (array_length_1d(argument0)) {
case 2:
    return argument0[0] * argument0[0] + argument0[1] * argument0[1];
case 3:
    return argument0[0] * argument0[0] + argument0[1] * argument0[1] + argument0[2] * argument0[2];
case 4:
    return argument0[0] * argument0[0] + argument0[1] * argument0[1] + argument0[2] * argument0[2] + argument0[3] * argument0[3];
}

return undefined;

#define MAE_VectorMultiplyMatrix
switch (array_length_1d(argument1)) {
case 4:
    if (array_length_1d(argument0) < 2)
        return undefined;
    
    var v;
    
    v[1] = argument0[0] * argument1[1] + argument0[1] * argument1[3];
    v[0] = argument0[0] * argument1[0] + argument0[1] * argument1[2];
    
    return v;
case 9:
    if (array_length_1d(argument0) < 3)
        return undefined;
    
    var v;
    
    v[2] = argument0[0] * argument1[2] + argument0[1] * argument1[5] + argument0[2] * argument1[8];
    v[1] = argument0[0] * argument1[1] + argument0[1] * argument1[4] + argument0[2] * argument1[7];
    v[0] = argument0[0] * argument1[0] + argument0[1] * argument1[3] + argument0[2] * argument1[6];
    
    return v;
case 16:
    if (array_length_1d(argument0) < 4) {
        if (array_length_1d(argument0) == 3)
            argument0[3] = 1;
        else
            return undefined;
    }
    
    var v;
    
    v[3] = argument0[0] * argument1[3] + argument0[1] * argument1[7] + argument0[2] * argument1[11] + argument0[3] * argument1[15];
    v[2] = argument0[0] * argument1[2] + argument0[1] * argument1[6] + argument0[2] * argument1[10] + argument0[3] * argument1[14];
    v[1] = argument0[0] * argument1[1] + argument0[1] * argument1[5] + argument0[2] * argument1[9] + argument0[3] * argument1[13];
    v[0] = argument0[0] * argument1[0] + argument0[1] * argument1[4] + argument0[2] * argument1[8] + argument0[3] * argument1[12];
    
    return v;
}

return undefined;

#define MAE_VectorNorm
var l = MAE_VectorMagnitude(argument0);

if (sign(l) != 0) {
    switch (array_length_1d(argument0)) {
    case 2:
        argument0[@ 0] /= l;
        argument0[@ 1] /= l;
        
        return argument0;
    case 3:
        argument0[@ 0] /= l;
        argument0[@ 1] /= l;
        argument0[@ 2] /= l;
                
        return argument0;
    case 4: 
        argument0[@ 0] /= l;
        argument0[@ 1] /= l;
        argument0[@ 2] /= l;
        argument0[@ 3] /= l;
        
        return argument0;
    }
}

return undefined;

#define MAE_VectorProject
if (array_length_1d(argument0) < 4) {
    for (var i = array_length_1d(argument0); i < 4; ++i)
        argument0[i] = 0;
    
    argument0[3] = 1;
}

var v = MAE_VectorMultiplyMatrix(argument0, argument1);

if (sign(v[3]) == 0)
    return undefined;

return MAE_VectorCreate((v[0] / v[3] + 1) / 2 * argument2[2] + argument2[0],
                  (-v[1] / v[3] + 1) / 2 * argument2[3] + argument2[1],
                  v[2] / v[3]);

#define MAE_VectorReflect
switch (array_length_1d(argument0)) {
case 2:
    var dot2 = 2 * (argument0[0] * argument1[0] + argument0[1] * argument1[1]);
    
    var v;
    
    v[1] = argument1[1] * dot2 - argument0[1];
    v[0] = argument1[0] * dot2 - argument0[0];
    
    return v;
case 3:
    var dot2 = 2 * (argument0[0] * argument1[0] + argument0[1] * argument1[1] + argument0[2] * argument1[2]);
    
    var v;
    
    v[2] = argument1[2] * dot2 - argument0[2];
    v[1] = argument1[1] * dot2 - argument0[1];
    v[0] = argument1[0] * dot2 - argument0[0];
    
    return v;
}

return undefined;

#define MAE_VectorSet
argument0[@ argument1] = argument2

return argument0;

#define MAE_VectorUnproject
return MAE_VectorUnprojectInverse(argument0, MAE_MatrixInverse(argument1), argument2);

#define MAE_VectorUnprojectInverse
if (array_length_1d(argument0) < 4) {
    for (var i = array_length_1d(argument0); i < 4; ++i)
        argument0[i] = 0;
    
    argument0[3] = 1;
}

argument0[0] =   (argument0[0] - argument2[0]) / argument2[2] * 2 - 1;
argument0[1] = -((argument0[1] - argument2[1]) / argument2[3] * 2 - 1);

var v = MAE_VectorMultiplyMatrix(argument0, argument1);

if (sign(v[3]) != 0)
    MAE_VectorDivide(v, v[3]);
else
    return undefined;

return MAE_VectorCreate(v[0], v[1], v[2]);

