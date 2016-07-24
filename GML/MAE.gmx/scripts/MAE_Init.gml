///MAE_Init(DLL = "MAE.dll");

/**
 * Description:
 *   Initializes the Engine
 *
 * Arguments:
 *   [1] - Filename of the DLL
 *
 * Returns:
 *   Returns true on success
 */

var _DLL = "MAE.dll";

if (argument_count > 0)
    _DLL = argument[0];

enum PARAM {
    BREAKING_IMPULSE_THRESHOLD,
    USE_FRAME_OFFSET,
    FRAMES,
    SOLVER_ITERATIONS,
    P2P_IMPULSE_CLAMP,
    P2P_DAMPING,
    P2P_TAU,
    P2P_PIVOTA,
    P2P_PIVOTB,
    SLIDER_DAMPING_DIR_ANG,
    SLIDER_DAMPING_DIR_LIN,
    SLIDER_DAMPING_LIM_ANG,
    SLIDER_DAMPING_LIM_LIN,
    SLIDER_DAMPING_ORTHO_ANG,
    SLIDER_DAMPING_ORTHO_LIN,
    SLIDER_LOWER_ANG_LIMIT,
    SLIDER_LOWER_LIN_LIMIT,
    SLIDER_MAX_ANG_MOTOR_FORCE,
    SLIDER_MAX_LIN_MOTOR_FORCE,
    SLIDER_POWERED_ANG_MOTOR,
    SLIDER_POWERED_LIN_MOTOR,
    SLIDER_RESTITUTION_DIR_ANG,
    SLIDER_RESTITUTION_DIR_LIN,
    SLIDER_RESTITUTION_LIM_ANG,
    SLIDER_RESTITUTION_LIM_LIN,
    SLIDER_RESTITUTION_ORTHO_ANG,
    SLIDER_RESTITUTION_ORTHO_LIN,
    SLIDER_SOFTNESS_DIR_ANG,
    SLIDER_SOFTNESS_DIR_LIN,
    SLIDER_SOFTNESS_LIM_ANG,
    SLIDER_SOFTNESS_LIM_LIN,
    SLIDER_SOFTNESS_ORTHO_ANG,
    SLIDER_SOFTNESS_ORTHO_LIN,
    SLIDER_TARGET_ANG_MOTOR_VELOCITY,
    SLIDER_TARGET_LIN_MOTOR_VELOCITY,
    SLIDER_UPPER_ANG_LIMIT,
    SLIDER_UPPER_LIN_LIMIT,
    GEAR_AXIS_A,
    GEAR_AXIS_B,
    GEAR_RATIO,
    HINGE_ANGULAR_ONLY,
    HINGE_AXIS,
    HINGE_LIMITS,
    HINGE_MAX_MOTOR_IMPULSE,
    HINGE_MOTOR_TARGET,
    HINGE_MOTOR_ENABLED,
    DOF_ANGULAR_LOWER_LIMIT,
    DOF_ANGULAR_UPPER_LIMIT,
    DOF_AXIS,
    DOF_LIMITS,
    DOF_LINEAR_LOWER_LIMIT,
    DOF_LINEAR_UPPER_LIMIT,
    DOF_SPRING_ENABLED,
    DOF_SPRING_DAMPING,
    DOF_SPRING_STIFFNESS,
    CONE_ANGULAR_ONLY,
    CONE_DAMPING,
    CONE_FIX_THRESH,
    CONE_LIMITS,
    CONE_MAX_MOTOR_IMPULSE,
    CONE_MAX_MOTOR_IMPULSE_NORMALIZED,
    CONE_MOTOR_TARGET,
    CONE_MOTOR_TARGET_CONSTRAINT_SPACE,
    CONE_MOTOR_ENABLED,
}

global._MADX9_MatStackFloat8 = external_define(_DLL, "MADX9_MatStackFloat8", dll_cdecl, ty_real, 8, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MADX9_MatStackFloat9 = external_define(_DLL, "MADX9_MatStackFloat9", dll_cdecl, ty_real, 9, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MADX9_MatStackClear = external_define(_DLL, "MADX9_MatStackClear", dll_cdecl, ty_real, 0);
global._MA_NavSetVertexBufferSize = external_define(_DLL, "MA_NavSetVertexBufferSize", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MA_NavGetPathPoint = external_define(_DLL, "MA_NavGetPathPoint", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAB_Vec = external_define(_DLL, "MAB_Vec", dll_cdecl, ty_real, 1, ty_real);
global._MAB_Quat = external_define(_DLL, "MAB_Quat", dll_cdecl, ty_real, 1, ty_real);
global._MAB_HitResult = external_define(_DLL, "MAB_HitResult", dll_cdecl, ty_real, 1, ty_real);
global._MAB_OverlapResult = external_define(_DLL, "MAB_OverlapResult", dll_cdecl, ty_real, 1, ty_real);
global._MAB_ConstraintParamTransform = external_define(_DLL, "MAB_ConstraintParamTransform", dll_cdecl, ty_real, 8, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MA_NavMeshCreate = external_define(_DLL, "MA_NavMeshCreate", dll_cdecl, ty_real, 0);
global._MA_NavMeshDestroy = external_define(_DLL, "MA_NavMeshDestroy", dll_cdecl, ty_real, 1, ty_real);
global._MA_NavMeshClear = external_define(_DLL, "MA_NavMeshClear", dll_cdecl, ty_real, 1, ty_real);
global._MA_NavMeshBeginBuild = external_define(_DLL, "MA_NavMeshBeginBuild", dll_cdecl, ty_real, 7, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MA_NavMeshEndBuild = external_define(_DLL, "MA_NavMeshEndBuild", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MA_NavMeshAddGMModel = external_define(_DLL, "MA_NavMeshAddGMModel", dll_cdecl, ty_real, 2, ty_real, ty_string);
global._MA_NavMeshAddVertexBuffer = external_define(_DLL, "MA_NavMeshAddVertexBuffer", dll_cdecl, ty_real, 3, ty_real, ty_string, ty_string);
global._MA_NavMeshAddLink = external_define(_DLL, "MA_NavMeshAddLink", dll_cdecl, ty_real, 9, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MA_NavMeshWaitForBuild = external_define(_DLL, "MA_NavMeshWaitForBuild", dll_cdecl, ty_real, 1, ty_real);
global._MA_NavMeshGetBuildStatus = external_define(_DLL, "MA_NavMeshGetBuildStatus", dll_cdecl, ty_real, 1, ty_real);
global._MA_NavMeshSetConfig = external_define(_DLL, "MA_NavMeshSetConfig", dll_cdecl, ty_real, 11, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MA_NavMeshSetAgentConfig = external_define(_DLL, "MA_NavMeshSetAgentConfig", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MA_NavMeshDebugDraw = external_define(_DLL, "MA_NavMeshDebugDraw", dll_cdecl, ty_real, 1, ty_real);
global._MA_NavMeshFindPath = external_define(_DLL, "MA_NavMeshFindPath", dll_cdecl, ty_real, 8, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MAB_BodyCreate = external_define(_DLL, "MAB_BodyCreate", dll_cdecl, ty_real, 8, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MAB_BodyDestroy = external_define(_DLL, "MAB_BodyDestroy", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyGetPosition = external_define(_DLL, "MAB_BodyGetPosition", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyGetRotationEuler = external_define(_DLL, "MAB_BodyGetRotationEuler", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyGetRotationQuat = external_define(_DLL, "MAB_BodyGetRotationQuat", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyGetLinearVelocity = external_define(_DLL, "MAB_BodyGetLinearVelocity", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyGetAngularVelocity = external_define(_DLL, "MAB_BodyGetAngularVelocity", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyGetAnisotropicFriction = external_define(_DLL, "MAB_BodyGetAnisotropicFriction", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyGetGravity = external_define(_DLL, "MAB_BodyGetGravity", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyGetAngularDamping = external_define(_DLL, "MAB_BodyGetAngularDamping", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyGetLinearDamping = external_define(_DLL, "MAB_BodyGetLinearDamping", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyGetFriction = external_define(_DLL, "MAB_BodyGetFriction", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyGetRestitution = external_define(_DLL, "MAB_BodyGetRestitution", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyGetRollingFriction = external_define(_DLL, "MAB_BodyGetRollingFriction", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyGetUserIndex = external_define(_DLL, "MAB_BodyGetUserIndex", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyGetDeactivationTime = external_define(_DLL, "MAB_BodyGetDeactivationTime", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyGetIgnore = external_define(_DLL, "MAB_BodyGetIgnore", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyIsStatic = external_define(_DLL, "MAB_BodyIsStatic", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyIsKinematic = external_define(_DLL, "MAB_BodyIsKinematic", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyIsActive = external_define(_DLL, "MAB_BodyIsActive", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyGetShape = external_define(_DLL, "MAB_BodyGetShape", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyGetGroup = external_define(_DLL, "MAB_BodyGetGroup", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyGetMask = external_define(_DLL, "MAB_BodyGetMask", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodySetPosition = external_define(_DLL, "MAB_BodySetPosition", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
global._MAB_BodySetRotationEuler = external_define(_DLL, "MAB_BodySetRotationEuler", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
global._MAB_BodySetRotationQuat = external_define(_DLL, "MAB_BodySetRotationQuat", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MAB_BodySetLinearVelocity = external_define(_DLL, "MAB_BodySetLinearVelocity", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
global._MAB_BodySetAngularVelocity = external_define(_DLL, "MAB_BodySetAngularVelocity", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
global._MAB_BodySetLinearFactor = external_define(_DLL, "MAB_BodySetLinearFactor", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
global._MAB_BodySetAngularFactor = external_define(_DLL, "MAB_BodySetAngularFactor", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MAB_BodySetAnisotropicFriction = external_define(_DLL, "MAB_BodySetAnisotropicFriction", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
global._MAB_BodySetGravity = external_define(_DLL, "MAB_BodySetGravity", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
global._MAB_BodySetDamping = external_define(_DLL, "MAB_BodySetDamping", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
global._MAB_BodySetFriction = external_define(_DLL, "MAB_BodySetFriction", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAB_BodySetRestitution = external_define(_DLL, "MAB_BodySetRestitution", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAB_BodySetRollingFriction = external_define(_DLL, "MAB_BodySetRollingFriction", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAB_BodySetUserIndex = external_define(_DLL, "MAB_BodySetUserIndex", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAB_BodySetShape = external_define(_DLL, "MAB_BodySetShape", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAB_BodySetIgnore = external_define(_DLL, "MAB_BodySetIgnore", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
global._MAB_BodySetGroupMask = external_define(_DLL, "MAB_BodySetGroupMask", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
global._MAB_BodySetDeactivationTime = external_define(_DLL, "MAB_BodySetDeactivationTime", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAB_BodyDisableDeactivation = external_define(_DLL, "MAB_BodyDisableDeactivation", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyActivate = external_define(_DLL, "MAB_BodyActivate", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyDeactivate = external_define(_DLL, "MAB_BodyDeactivate", dll_cdecl, ty_real, 1, ty_real);
global._MAB_BodyApplyCentralImpulse = external_define(_DLL, "MAB_BodyApplyCentralImpulse", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MAB_BodyApplyCentralForce = external_define(_DLL, "MAB_BodyApplyCentralForce", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MAB_BodyApplyImpulse = external_define(_DLL, "MAB_BodyApplyImpulse", dll_cdecl, ty_real, 7, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MAB_BodyApplyForce = external_define(_DLL, "MAB_BodyApplyForce", dll_cdecl, ty_real, 7, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MAB_BodyApplyTorque = external_define(_DLL, "MAB_BodyApplyTorque", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MAB_BodyApplyTorqueImpulse = external_define(_DLL, "MAB_BodyApplyTorqueImpulse", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MAB_ConstraintCreateP2P = external_define(_DLL, "MAB_ConstraintCreateP2P", dll_cdecl, ty_real, 11, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MAB_ConstraintCreateFixed = external_define(_DLL, "MAB_ConstraintCreateFixed", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAB_ConstraintCreateSlider = external_define(_DLL, "MAB_ConstraintCreateSlider", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
global._MAB_ConstraintCreateGear = external_define(_DLL, "MAB_ConstraintCreateGear", dll_cdecl, ty_real, 10, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MAB_ConstraintCreateHinge = external_define(_DLL, "MAB_ConstraintCreateHinge", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
global._MAB_ConstraintCreate6DOF = external_define(_DLL, "MAB_ConstraintCreate6DOF", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
global._MAB_ConstraintCreateSpring6DOF = external_define(_DLL, "MAB_ConstraintCreateSpring6DOF", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
global._MAB_ConstraintCreateConeTwist = external_define(_DLL, "MAB_ConstraintCreateConeTwist", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
global._MAB_ConstraintDestroy = external_define(_DLL, "MAB_ConstraintDestroy", dll_cdecl, ty_real, 1, ty_real);
global._MAB_ConstraintSetParam = external_define(_DLL, "MAB_ConstraintSetParam", dll_cdecl, ty_real, 8, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MAB_ConstraintSetEnabled = external_define(_DLL, "MAB_ConstraintSetEnabled", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAB_ConstraintGetAppliedImpulse = external_define(_DLL, "MAB_ConstraintGetAppliedImpulse", dll_cdecl, ty_real, 1, ty_real);
global._MAB_ShapeCreateSphere = external_define(_DLL, "MAB_ShapeCreateSphere", dll_cdecl, ty_real, 1, ty_real);
global._MAB_ShapeCreateBox = external_define(_DLL, "MAB_ShapeCreateBox", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
global._MAB_ShapeCreateCapsule = external_define(_DLL, "MAB_ShapeCreateCapsule", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
global._MAB_ShapeCreateCylinder = external_define(_DLL, "MAB_ShapeCreateCylinder", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
global._MAB_ShapeCreateCone = external_define(_DLL, "MAB_ShapeCreateCone", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
global._MAB_ShapeCreatePlane = external_define(_DLL, "MAB_ShapeCreatePlane", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
global._MAB_ShapeCreateCompound = external_define(_DLL, "MAB_ShapeCreateCompound", dll_cdecl, ty_real, 0);
global._MAB_ShapeAddChild = external_define(_DLL, "MAB_ShapeAddChild", dll_cdecl, ty_real, 9, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MAB_ShapeRemoveChild = external_define(_DLL, "MAB_ShapeRemoveChild", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAB_ShapeUpdateChildTransform = external_define(_DLL, "MAB_ShapeUpdateChildTransform", dll_cdecl, ty_real, 9, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MAB_ShapeCreateTriMesh = external_define(_DLL, "MAB_ShapeCreateTriMesh", dll_cdecl, ty_real, 4, ty_string, ty_real, ty_real, ty_real);
global._MAB_ShapeCreateConvexHull = external_define(_DLL, "MAB_ShapeCreateConvexHull", dll_cdecl, ty_real, 2, ty_string, ty_real);
global._MAB_ShapeDestroy = external_define(_DLL, "MAB_ShapeDestroy", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAB_ShapeDestroyAll = external_define(_DLL, "MAB_ShapeDestroyAll", dll_cdecl, ty_real, 0);
global._MAB_ShapeSetMargin = external_define(_DLL, "MAB_ShapeSetMargin", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAB_ShapeSetScaling = external_define(_DLL, "MAB_ShapeSetScaling", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
global._MAB_WorldCreate = external_define(_DLL, "MAB_WorldCreate", dll_cdecl, ty_real, 1, ty_real);
global._MAB_WorldDestroy = external_define(_DLL, "MAB_WorldDestroy", dll_cdecl, ty_real, 1, ty_real);
global._MAB_WorldStep = external_define(_DLL, "MAB_WorldStep", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
global._MAB_WorldExists = external_define(_DLL, "MAB_WorldExists", dll_cdecl, ty_real, 0);
global._MAB_WorldSetGravity = external_define(_DLL, "MAB_WorldSetGravity", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
global._MAB_WorldGetGravity = external_define(_DLL, "MAB_WorldGetGravity", dll_cdecl, ty_real, 0);
global._MAB_WorldGetBodyCount = external_define(_DLL, "MAB_WorldGetBodyCount", dll_cdecl, ty_real, 0);
global._MAB_WorldGetConstraintCount = external_define(_DLL, "MAB_WorldGetConstraintCount", dll_cdecl, ty_real, 0);
global._MAB_WorldDebugDraw = external_define(_DLL, "MAB_WorldDebugDraw", dll_cdecl, ty_real, 0);
global._MAB_WorldRaycast = external_define(_DLL, "MAB_WorldRaycast", dll_cdecl, ty_real, 8, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MAB_WorldSweep = external_define(_DLL, "MAB_WorldSweep", dll_cdecl, ty_real, 9, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MAB_WorldOverlap = external_define(_DLL, "MAB_WorldOverlap", dll_cdecl, ty_real, 10, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MADX9_Init = external_define(_DLL, "MADX9_Init", dll_cdecl, ty_real, 1, ty_string);
global._MADX9_Free = external_define(_DLL, "MADX9_Free", dll_cdecl, ty_real, 0);
global._MADX9_MD2Load = external_define(_DLL, "MADX9_MD2Load", dll_cdecl, ty_real, 3, ty_string, ty_real, ty_real);
global._MADX9_MD2GetFrames = external_define(_DLL, "MADX9_MD2GetFrames", dll_cdecl, ty_real, 1, ty_real);
global._MADX9_MD2Render = external_define(_DLL, "MADX9_MD2Render", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
global._MADX9_MD2Destroy = external_define(_DLL, "MADX9_MD2Destroy", dll_cdecl, ty_real, 1, ty_real);
global._MAE_MPMLoad = external_define(_DLL, "MAE_MPMLoad", dll_cdecl, ty_real, 1, ty_string);
global._MAE_MPMDestroy = external_define(_DLL, "MAE_MPMDestroy", dll_cdecl, ty_real, 1, ty_real);
global._MAE_MPMRender = external_define(_DLL, "MAE_MPMRender", dll_cdecl, ty_real, 1, ty_real);
global._MADX9_XLoad = external_define(_DLL, "MADX9_XLoad", dll_cdecl, ty_real, 2, ty_string, ty_string);
global._MADX9_XRender = external_define(_DLL, "MADX9_XRender", dll_cdecl, ty_real, 1, ty_real);
global._MADX9_XDestroy = external_define(_DLL, "MADX9_XDestroy", dll_cdecl, ty_real, 1, ty_real);
global._MADX9_ParticleEmitterCreate = external_define(_DLL, "MADX9_ParticleEmitterCreate", dll_cdecl, ty_real, 1, ty_real);
global._MADX9_ParticleEmitterSetParticleCount = external_define(_DLL, "MADX9_ParticleEmitterSetParticleCount", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
global._MADX9_ParticleEmitterSetParticleLife = external_define(_DLL, "MADX9_ParticleEmitterSetParticleLife", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
global._MADX9_ParticleEmitterSetParticleSize = external_define(_DLL, "MADX9_ParticleEmitterSetParticleSize", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
global._MADX9_ParticleEmitterSetParticlePos = external_define(_DLL, "MADX9_ParticleEmitterSetParticlePos", dll_cdecl, ty_real, 7, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MADX9_ParticleEmitterSetParticleAcc = external_define(_DLL, "MADX9_ParticleEmitterSetParticleAcc", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
global._MADX9_ParticleEmitterSetParticleVel = external_define(_DLL, "MADX9_ParticleEmitterSetParticleVel", dll_cdecl, ty_real, 7, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MADX9_ParticleEmitterSetParticleCol = external_define(_DLL, "MADX9_ParticleEmitterSetParticleCol", dll_cdecl, ty_real, 9, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MADX9_ParticleSystemCreate = external_define(_DLL, "MADX9_ParticleSystemCreate", dll_cdecl, ty_real, 0);
global._MADX9_ParticleSystemDestroy = external_define(_DLL, "MADX9_ParticleSystemDestroy", dll_cdecl, ty_real, 1, ty_real);
global._MADX9_ParticleSystemUpdate = external_define(_DLL, "MADX9_ParticleSystemUpdate", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MADX9_ParticleSystemRender = external_define(_DLL, "MADX9_ParticleSystemRender", dll_cdecl, ty_real, 1, ty_real);
global._MADX9_ParticleSystemGetParticleCount = external_define(_DLL, "MADX9_ParticleSystemGetParticleCount", dll_cdecl, ty_real, 1, ty_real);
global._MADX9_ParticleSystemSetParticleCount = external_define(_DLL, "MADX9_ParticleSystemSetParticleCount", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MADX9_ParticleSystemSetTexture = external_define(_DLL, "MADX9_ParticleSystemSetTexture", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MADX9_TextureCreateFromFile = external_define(_DLL, "MADX9_TextureCreateFromFile", dll_cdecl, ty_real, 2, ty_string, ty_real);
global._MADX9_TextureCreateFromFileInMemory = external_define(_DLL, "MADX9_TextureCreateFromFileInMemory", dll_cdecl, ty_real, 3, ty_string, ty_real, ty_real);
global._MADX9_TextureDestroy = external_define(_DLL, "MADX9_TextureDestroy", dll_cdecl, ty_real, 1, ty_real);
global._MADX9_TextureSet = external_define(_DLL, "MADX9_TextureSet", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAE_ShaderCreate = external_define(_DLL, "MAE_ShaderCreate", dll_cdecl, ty_real, 2, ty_string, ty_string);
global._MAE_ShaderDestroy = external_define(_DLL, "MAE_ShaderDestroy", dll_cdecl, ty_real, 1, ty_real);
global._MAE_ShaderFindConstant = external_define(_DLL, "MAE_ShaderFindConstant", dll_cdecl, ty_real, 2, ty_real, ty_string);
global._MAE_ShaderGetLocation = external_define(_DLL, "MAE_ShaderGetLocation", dll_cdecl, ty_real, 2, ty_real, ty_string);
global._MAE_ShaderSetSampler = external_define(_DLL, "MAE_ShaderSetSampler", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
global._MAE_ShaderSet = external_define(_DLL, "MAE_ShaderSet", dll_cdecl, ty_real, 1, ty_real);
global._MAE_ShaderSetConstantFloat = external_define(_DLL, "MAE_ShaderSetConstantFloat", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
global._MAE_ShaderSetConstantMat3 = external_define(_DLL, "MAE_ShaderSetConstantMat3", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAE_ShaderSetConstantMat4 = external_define(_DLL, "MAE_ShaderSetConstantMat4", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAE_ShaderSetConstantVec2 = external_define(_DLL, "MAE_ShaderSetConstantVec2", dll_cdecl, ty_real, 4, ty_real, ty_real, ty_real, ty_real);
global._MAE_ShaderSetConstantVec3 = external_define(_DLL, "MAE_ShaderSetConstantVec3", dll_cdecl, ty_real, 5, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MAE_ShaderSetConstantVec4 = external_define(_DLL, "MAE_ShaderSetConstantVec4", dll_cdecl, ty_real, 6, ty_real, ty_real, ty_real, ty_real, ty_real, ty_real);
global._MAE_ShaderReset = external_define(_DLL, "MAE_ShaderReset", dll_cdecl, ty_real, 0);


enum FmodLoopMode {
    OFF,
    ON,
    BIDI
};
enum FmodSpeakerMode {
    Default,
    Raw,
    Mono,
    Stereo,
    Quad,
    FivePointOne,
    SevenPointOne,
    Max,
    ForceInt
};
global._MAE_FmodCreate = external_define(_DLL, "MAE_FmodCreate", dll_cdecl, ty_real, 0);
global._MAE_FmodInitialize = external_define(_DLL, "MAE_FmodInitialize", dll_cdecl, ty_real, 0);
global._MAE_FmodUpdate = external_define(_DLL, "MAE_FmodUpdate", dll_cdecl, ty_real, 0);
global._MAE_FmodShutdown = external_define(_DLL, "MAE_FmodShutdown", dll_cdecl, ty_real, 0);
global._MAE_FmodSetSoftwareFormat = external_define(_DLL, "MAE_FmodSetSoftwareFormat", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAE_FmodSetMaxChannels = external_define(_DLL, "MAE_FmodSetMaxChannels", dll_cdecl, ty_real, 1, ty_real);
global._MAE_FmodGetSampleRate = external_define(_DLL, "MAE_FmodGetSampleRate", dll_cdecl, ty_real, 0);
global._MAE_FmodGetCPUUsage = external_define(_DLL, "MAE_FmodGetCPUUsage", dll_cdecl, ty_real, 0);
global._MAE_FmodGetSounds = external_define(_DLL, "MAE_FmodGetSounds", dll_cdecl, ty_real, 0);

global._MAE_FmodSoundLoad = external_define(_DLL, "MAE_FmodSoundLoad", dll_cdecl, ty_real, 2, ty_string, ty_real);
global._MAE_FmodSoundFree = external_define(_DLL, "MAE_FmodSoundFree", dll_cdecl, ty_real, 1, ty_real);
global._MAE_FmodSoundPlay = external_define(_DLL, "MAE_FmodSoundPlay", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAE_FmodSoundSetLoopMode = external_define(_DLL, "MAE_FmodSoundSetLoopMode", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAE_FmodSoundSetLoopPoints = external_define(_DLL, "MAE_FmodSoundSetLoopPoints", dll_cdecl, ty_real, 3, ty_real, ty_real, ty_real);
global._MAE_FmodSoundGetType = external_define(_DLL, "MAE_FmodSoundGetType", dll_cdecl, ty_string, 1, ty_real);

global._MAE_FmodChannelCreate = external_define(_DLL, "MAE_FmodChannelCreate", dll_cdecl, ty_real, 0);
global._MAE_FmodChannelDelete = external_define(_DLL, "MAE_FmodChannelDelete", dll_cdecl, ty_real, 1, ty_real);
global._MAE_FmodChannelPause = external_define(_DLL, "MAE_FmodChannelPause", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAE_FmodChannelStop = external_define(_DLL, "MAE_FmodChannelStop", dll_cdecl, ty_real, 1, ty_real);
global._MAE_FmodChannelSetPosition = external_define(_DLL, "MAE_FmodChannelSetPosition", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAE_FmodChannelSetVolume = external_define(_DLL, "MAE_FmodChannelSetVolume", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAE_FmodChannelSetFrequency = external_define(_DLL, "MAE_FmodChannelSetFrequency", dll_cdecl, ty_real, 2, ty_real, ty_real);
global._MAE_FmodChannelSetPitch = external_define(_DLL, "MAE_FmodChannelSetPitch", dll_cdecl, ty_real, 2, ty_real, ty_real);


global._MAEDLL = _DLL;

return external_call(global._MADX9_Init, window_device());
