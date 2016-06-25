///MAE_PhysVertexBufferCreate([size])

if(argument_count == 0) return buffer_create(64, buffer_grow, 4);
return buffer_create(argument[0], buffer_grow, 4);

