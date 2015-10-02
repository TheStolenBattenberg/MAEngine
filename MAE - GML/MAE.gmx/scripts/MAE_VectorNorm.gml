///MAE_VectorNorm(ref_v);

/**
 * To-do:
 *      Add Description.
 *
 */
var l = MAE_VectorMagnitude(argument0);

if (l != 0) {
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
