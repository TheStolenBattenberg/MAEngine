///MAE_RegionObjectIntersect(region, object);

/**
 * For checking if an object is inside a region.
 * Objects must have a 'z' variable!
 */
 
if(argument1.x > argument0[| 0] && argument1.x < argument0[| 3])
{
    if(argument1.y > argument0[| 1] && argument1.y < argument0[| 4])
    {
        if(argument1.z > argument0[| 2] && argument1.z < argument0[| 5])
        {
            return true;
        }
    }
}
return false;
