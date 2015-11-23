///MAE_ErrorSetFlags(flags)

/**
 * Description:
 *   Sets error handling flags.
 *
 * Arguments:
 *   [1] - Error flags (ERROR_*)
 *
 * Returns:
 *   0 on Error, 1 on success.
 */

return external_call(global.MADX9_ErrorSetFlags, argument0);
