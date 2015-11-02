///MAE_AnimationUpdate(FPS);
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
