#define MAE_AnimationCreate
ANI_TIME = 0;
ANI_FRAME_1 = 0;
ANI_FRAME_2 = 0;
ANI_SET[0, 0] = noone;
ANI_SET[0, 1] = noone;
ANI_SETS = 0;
ANI_SET_INDEX = 0;

#define MAE_AnimationUpdate
ANI_TIME += argument0 / room_speed;
if(ANI_TIME >= 1)
{
    ANI_FRAME_1++;
    if(ANI_FRAME_1 > ANI_SET[ANI_SET_INDEX, 1])
    {
        ANI_FRAME_1 = ANI_SET[ANI_SET_INDEX, 0];
    }
    if(ANI_FRAME_1 == ANI_SET[ANI_SET_INDEX, 1])
    {
        ANI_FRAME_2 = ANI_SET[ANI_SET_INDEX, 0];
    }else{
            ANI_FRAME_2++; 
    }
    ANI_TIME = 0;
}

#define MAE_AnimationAdd
ANI_SET[ANI_SETS, 0] = argument0;
ANI_SET[ANI_SETS, 1] = argument1;
ANI_SETS++;
return ANI_SETS-1;

#define MAE_AnimationSet
ANI_SET_INDEX = argument0;
ANI_FRAME_1 = ANI_SET[argument0, 0];
ANI_FRAME_2 = ANI_SET[argument0, 0]+1;

#define MAE_AnimationGetFrame
return ANI_FRAME_1;

#define MAE_AnimationGetFrameNext
return ANI_FRAME_2;

#define MAE_AnimationGetTween
return ANI_TIME - floor(ANI_TIME);

