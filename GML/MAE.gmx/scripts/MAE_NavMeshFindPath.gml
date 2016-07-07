///MAE_NavMeshFindPath(index, start_x, start_y, start_z, end_x, end_y, end_z, check_size)

var result = external_call(global.MA_NavMeshFindPath, argument0, argument1, argument2, argument3, argument4, argument5, argument6, argument7);
if(result <= 0) return result;
var _path;
for(var i=0; i<result; i++){
    _path[i] = MAE_VectorCreate(external_call(global.MA_NavGetPathPoint, i, 0),
                                external_call(global.MA_NavGetPathPoint, i, 1),
                                external_call(global.MA_NavGetPathPoint, i, 2));
}
return _path;

