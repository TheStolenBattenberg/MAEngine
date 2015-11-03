///MAE_PhysWorldSetRotation(BodyID, rotation)
/*
Accepts a 3-component vector of euler angles, a quaternion, or 3 seperate euler angles.
*/

if(argument_count == 2){
    var rot = argument[1];
    if(MAE_VectorIsVec3(rot)) return external_call(global.MAB_BodySetRotationEuler, argument[0], rot[0], rot[1], rot[2]);
    else if(MAE_QuaternionIsQuaternion(rot)) return external_call(global.MAB_BodySetRotationQuat, argument[0], rot[0], rot[1], rot[2], rot[3]);
    return false;
}
return external_call(global.MAB_WorldSetRotationEuler, argument[0], argument[1], argument[2], argument[3]);
