///MAE_ToVec4(...);

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
