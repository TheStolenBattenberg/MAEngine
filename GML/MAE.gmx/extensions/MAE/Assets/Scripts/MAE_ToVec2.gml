///MAE_ToVec2(...);

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
