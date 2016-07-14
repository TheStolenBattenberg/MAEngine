///MAE_PhysConstraintSetParam(constraint,param,...);

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

if(argument_count == 3){
    if(MAE_VectorIsVec3(argument[2])){
        var vec = argument[2];
        return external_call(global._MAB_ConstraintSetParam, argument[0], argument[1], vec[0], vec[1], vec[2], 0, 0, 0);
    }
    if(MAE_QuaternionIsQuaternion(argument[2])){
        var quat = argument[2];
        external_call(global.MAB_ConstraintParamTransform, 0, 0, 0, 0, quat[0], quat[1], quat[2], quat[3]);
        return external_call(global.MAV_ConstraintSetParam, argument[0], argument[1], 0, 0, 0, 0, 0, 0);
    }
    return external_call(global._MAB_ConstraintSetParam, argument[0], argument[1], argument[2], 0, 0, 0, 0, 0);
}
if(argument_count == 4){
    if(MAE_VectorIsVec3(argument[2]) && MAE_VectorIsVec3(argument[3])){
        vec1 = argument[2];
        vec2 = argument[3];
        return external_call(global._MAB_ConstraintSetParam, argument[0], argument[1], vec1[0], vec1[1], vec1[2], vec2[0], vec2[1], vec2[2]);
    }
    if(MAE_MatrixIsMat4(argument[2]) && MAE_MatrixIsMat4(argument[3])){
        var trans1 = argument[2];
        var quat1 = MAE_QuaternionCreateRotationMatrix(trans1);
        external_call(global.MAB_ConstraintParamTransform, 0, trans1[12], trans1[13], trans1[14], quat1[0], quat1[1], quat1[2], quat1[3]);
        var trans2 = argument[3];
        var quat2 = MAE_QuaternionCreateRotationMatrix(trans2);
        external_call(global.MAB_ConstraintParamTransform, 0, trans2[12], trans2[13], trans2[14], quat2[0], quat2[1], quat2[2], quat2[3]);
        return external_call(global._MAB_ConstraintSetParam, argument[0], argument[1], 0, 0, 0, 0, 0, 0);
    }
    return external_call(global._MAB_ConstraintSetParam, argument[0], argument[1], argument[2], argument[3], 0, 0, 0, 0);
}
if(argument_count == 5) return external_call(global._MAB_ConstraintSetParam, argument[0], argument[1], argument[2], argument[3], argument[4], 0, 0, 0);
if(argument_count == 6) return external_call(global._MAB_ConstraintSetParam, argument[0], argument[1], argument[2], argument[3], argument[4], argument[5], 0, 0);
if(argument_count == 7) return external_call(global._MAB_ConstraintSetParam, argument[0], argument[1], argument[2], argument[3], argument[4], argument[5], argument[6], 0);
if(argument_count == 8) return external_call(global._MAB_ConstraintSetParam, argument[0], argument[1], argument[2], argument[3], argument[4], argument[5], argument[6], argument[7]);
