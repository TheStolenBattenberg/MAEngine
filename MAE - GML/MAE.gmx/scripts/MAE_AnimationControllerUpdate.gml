///MAE_AnimationControllerUpdate();
ANI_TIME += 5 / room_speed;
if(ANI_TIME > ANI_SET[ANI_SET_INDEX, 1])
{
    ANI_TIME = ANI_SET[ANI_SET_INDEX, 0];
}
