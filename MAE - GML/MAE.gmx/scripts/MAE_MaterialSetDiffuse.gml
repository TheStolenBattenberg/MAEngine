///MAE_MaterialSetDiffuse(index, r, g, b, a);

if(argument1 == 0) { var r = 0; }else{ var r = argument1/255; }
if(argument2 == 0) { var g = 0; }else{ var g = argument2/255; }
if(argument3 == 0) { var b = 0; }else{ var b = argument3/255; }
if(argument4 == 0) { var a = 0; }else{ var a = argument4/255; }
return external_call(global.MADX9_MaterialSetDiffuse, ty_real, r, g, b, a);
