///MAE_PhysBodySetLinearFactor(body, x, y, z)
///MAE_PhysBodySetLinearFactor(body, factor)
///MAE_PhysBodySetLinearFactor(body, vec)

/**
 * Description:
 *   Sets the linear factor of a physics body. This can be used to restrict movement per axis.
 *   You could limit the physics engine to a 2D plane, for example.
 *
 * Arguments:
 *   [0]   - Body
 *   [1-3] - X, Y, Z, factors
 *
 * Returns:
 *   Success
 */

if(argument_count == 2){
    var vec = argument[1];
    if(MAE_VectorIsVec3(vec)) return external_call(global.MAB_BodySetLinearFactor, argument[0], vec[0], vec[1], vec[2]);
    else return external_call(global.MAB_BodySetLinearFactor, argument[0], vec, vec, vec);
}
return external_call(global.MAB_BodySetLinearFactor, argument[0], argument[1], argument[2], argument[3]);
