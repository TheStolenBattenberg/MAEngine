///MAE_ModelXLoad(model,[basedir]);

/**
 * Description:
 *   Loads X Model and its textures.
 *
 * Arguments:
 *   [1] - X File.
 *   [2] - Texture base directory.
 *
 * Returns:
 *   0 on Error, 1 on success. 
 */
var baseDir;

if (argument_count > 1)
    baseDir = argument[1];
else
    baseDir = filename_dir(argument[0]);

return external_call(global.MADX9_XLoad, argument[0], baseDir);
