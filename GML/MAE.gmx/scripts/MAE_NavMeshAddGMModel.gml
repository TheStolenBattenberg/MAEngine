///MAE_NavMeshAddGMModel(index, filename, matrix)

external_call(global.MADX9_MatStackFloat8, argument2[0], argument2[4], argument2[8],  argument2[12], argument2[1], argument2[5], argument2[9],  argument2[13]);
external_call(global.MADX9_MatStackFloat8, argument2[2], argument2[6], argument2[10], argument2[14], argument2[3], argument2[7], argument2[11], argument2[15]);
return external_call(global.MA_NavMeshAddGMModel, argument0, argument1);

