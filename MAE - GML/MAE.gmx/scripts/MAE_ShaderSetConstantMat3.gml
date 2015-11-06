///MAE_ShaderSetConstantMat3(index,shd,c,mat)
external_call(global.MADX9_MatStackFloat, argument3[0], argument3[3], argument3[6], argument3[1]);
external_call(global.MADX9_MatStackFloat, argument3[4], argument3[7], argument3[2], argument3[5]);
external_call(global.MADX9_MatStackFloat, argument3[8], 0, 0, 0);

var r = external_call(global.MADX9_ShaderSetConstantMat3, argument0, argument1, argument2);

external_call(global.MADX9_MatStackClear);

return r;
