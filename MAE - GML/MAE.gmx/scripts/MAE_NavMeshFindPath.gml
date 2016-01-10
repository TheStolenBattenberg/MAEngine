///MAE_NavMeshFindPath(index, start_poly, end_poly, start_x, start_y, start_z, end_x, end_y, end_z)

var result = external_call(global.MA_NavMeshFindPath, argument0, argument1, argument2, argument3, argument4, argument5, argument6, argument7, argument8);
if(result <= 0) return result;
var _path;
var _len = external_call(global.MA_NavGetPathLength);
for(var i=0; i<_len; i++){
    external_call(global.MA_NavGetPathPoint, i);
    _path[i] = MAE_VectorCreate(external_call(global.MA_NavGetVec, 0), external_call(global.MA_NavGetVec, 1), external_call(global.MA_NavGetVec, 2));
}
return _path;

