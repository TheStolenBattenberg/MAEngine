///MAE_QuaternionCreateRotationMatrix(m);

/**
 * To-do:
 *      Add Description.
 *
 */
var q;

var trace = argument0[0]  + argument0[4] + argument0[8];

if (trace > 0) {
    var s = 0.5 / sqrt(trace + 1);
    
    q[3] = 0.25 / s;
    q[2] = (argument0[1] - argument0[3]) * s;
    q[1] = (argument0[6] - argument0[2]) * s;
    q[0] = (argument0[5] - argument0[7]) * s;
}
else if ((argument0[0] > argument0[4]) && (argument0[0] > argument0[8])) {
    var s = 2 * sqrt(1 + argument0[0] - argument0[4] - argument0[8]);
    
    q[3] = (argument0[5] - argument0[7]) / s;
    q[2] = (argument0[6] + argument0[2]) / s;
    q[1] = (argument0[3] + argument0[1]) / s;
    q[0] = 0.25 * s;
}
else if (argument0[4] > argument0[8]) {
    var s = 2 * sqrt(1 + argument0[4] - argument0[0] - argument0[8]);
    
    q[3] = (argument0[6] - argument0[2]) / s;
    q[2] = (argument0[7] + argument0[5]) / s;
    q[1] = 0.25 * s;
    q[0] = (argument0[3] + argument0[1]) / s;
}
else {
    var s = 2 * sqrt(1 + argument0[8] - argument0[0] - argument0[4]);
    
    q[3] = (argument0[1] - argument0[3]) / s;
    q[2] = 0.25 * s;
    q[1] = (argument0[7] + argument0[5]) / s;
    q[0] = (argument0[6] + argument0[2]) / s;
}

return q;
