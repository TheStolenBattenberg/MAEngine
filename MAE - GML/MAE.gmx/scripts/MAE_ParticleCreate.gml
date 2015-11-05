///MAE_ParticleCreate(type);

/**
 * TO-DO:
 * - Add Error Handling
 * - Write Description
 */
var ds = ds_list_create();
ds[| 0] = argument0;
ds[| 1] = -1;
ds[| 2] = 0.5;
ds[| 3] = 1.0;
ds[| 4] = 255;
ds[| 5] = 255;
ds[| 6] = 255;
ds[| 7] = 255;
ds[| 8] = 255;
ds[| 9] = 255;
ds[| 10] = 0.75;
ds[| 11] = 1.0;
ds[| 12] = bm_normal;
ds[| 13] = 60;
ds[| 14] = 120;
return ds;