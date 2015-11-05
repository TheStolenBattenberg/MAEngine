//MAE_AnimationAdd(Frame_Start, Frame_End);

/**
 * Description:
 *   Adds a animation.
 *
 * Arguments:
 *   [1] First Frame of Animation.
 *   [2] Last Frame of Animation.
 *
 * Returns:
 *   Animation Index.
 */
 
ANI_SET[ANI_SETS, 0] = argument0;
ANI_SET[ANI_SETS, 1] = argument1;
ANI_SETS++;
return ANI_SETS-1;
