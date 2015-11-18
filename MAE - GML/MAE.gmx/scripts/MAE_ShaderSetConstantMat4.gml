///MAE_ShaderSetConstantMat4(index,shd,c,mat)
external_call(global.MADX9_MatStackFloat8, argument3[0], argument3[4], argument3[8],  argument3[12], argument3[1], argument3[5], argument3[9],  argument3[13]);
external_call(global.MADX9_MatStackFloat8, argument3[2], argument3[6], argument3[10], argument3[14], argument3[3], argument3[7], argument3[11], argument3[15]);

var r = external_call(global.MADX9_ShaderSetConstantMat4, argument0, argument1, argument2);

external_call(global.MADX9_MatStackClear);

return r;
