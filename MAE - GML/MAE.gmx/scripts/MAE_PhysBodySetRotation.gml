///MAE_PhysBodySetRotation(body, rotation)
///MAE_PhysBodySetRotation(body, xrot, yrot, zrot)

/**
 * Description:
 *   Sets the rotation of a physics body.
 *
 * Arguments:
 *   [0] - Body
 *   [1] - Rotation. Can be a vector of euler angles or a quaternion.
 *
 * Returns:
 *   Success
 */

if(argument_count == 2){
    var rot = argument[1];
    if(MAE_VectorIsVec3(rot)) return external_call(global.MAB_BodySetRotationEuler, argument[0], rot[0], rot[1], rot[2]);
    else if(MAE_QuaternionIsQuaternion(rot)) return external_call(global.MAB_BodySetRotationQuat, argument[0], rot[0], rot[1], rot[2], rot[3]);
    return false;
}
return external_call(global.MAB_BodySetRotationEuler, argument[0], argument[1], argument[2], argument[3]);
