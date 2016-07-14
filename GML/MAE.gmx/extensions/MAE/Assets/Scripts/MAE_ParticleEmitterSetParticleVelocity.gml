///MAE_ParticleEmitterSetParticleVelocity(index,min,max);

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

var minVec = argument1, maxVec = argument2;

return external_call(global._MADX9_ParticleEmitterSetParticleVel, argument0, minVec[0], minVec[1], minVec[2], maxVec[0], maxVec[1], maxVec[2]);
