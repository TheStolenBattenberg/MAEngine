///MAE_MaterialSetSpecularPower(index, power);

if(argument1 == 0) { var pow = 0; }else{ var pow = argument1/255; }
return external_call(global.MADX9_MaterialSetSpecularPower, ty_real, pow);
