#define MAE_PhysVertexBufferCreate
return buffer_create(argument0, buffer_grow, 4);


#define MAE_PhysVertexBufferAddTriangle
buffer_write(argument0, buffer_f32, argument1);
buffer_write(argument0, buffer_f32, argument2);
buffer_write(argument0, buffer_f32, argument3);
buffer_write(argument0, buffer_f32, argument4);
buffer_write(argument0, buffer_f32, argument5);
buffer_write(argument0, buffer_f32, argument6);
buffer_write(argument0, buffer_f32, argument7);
buffer_write(argument0, buffer_f32, argument8);
buffer_write(argument0, buffer_f32, argument9);


#define MAE_PhysVertexBufferAddVertex
buffer_write(argument0, buffer_f32, argument1);
buffer_write(argument0, buffer_f32, argument2);
buffer_write(argument0, buffer_f32, argument3);


#define MAE_PhysVertexBufferDestroy
buffer_delete(argument0);


