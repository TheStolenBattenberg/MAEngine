///MAE_ParticleEmitterSetParticleAcceleration(index,acceleration);

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

var acceleration = argument1;

return external_call(global._MADX9_ParticleEmitterSetParticleAcc, argument0, acceleration[0], acceleration[1], acceleration[2]);
