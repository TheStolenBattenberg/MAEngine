///MAE_BufferPoke(ind,offset,buffer,bufofs,length)
external_call(global.MADX9_BufferSetPointer, buffer_get_address(argument2));
return external_call(global.MADX9_BufferPoke, argument0, argument1, argument3, argument4);
