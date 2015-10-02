///MAE_VectorUnprojectInverse(v, m, viewport);

/**
 * To-do:
 *      Add Description.
 *
 */
if (array_length_1d(argument0) < 4) {
    for (var i = array_length_1d(argument0); i < 4; ++i)
        argument0[i] = 0;
    
    argument0[3] = 1;
}

argument0[0] =   (argument0[0] - argument2[0]) / argument2[2] * 2 - 1;
argument0[1] = -((argument0[1] - argument2[1]) / argument2[3] * 2 - 1);

var v = MAE_VectorMultiplyMatrix(argument0, argument1);

if (v[3] != 0)
    MAE_VectorDivide(v, v[3]);

return MAE_VectorCreate(v[0], v[1], v[2]);
