///MAE_VectorCreate(...);

/**
 * Description:
 *   Creates a vector.
 * 
 * Arguments:
 *   [2-4] - Vector Value.
 *
 * Return:
 *   Vector ID.
 */
 
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
