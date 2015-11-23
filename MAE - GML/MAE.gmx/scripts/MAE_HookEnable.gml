///MAE_HookEnable(action)

/**
 * Description:
 *   Enables a action in the hook class.
 *
 * Arguments:
 *   [1] - Actions (HOOK_ACTION*)
 *
 * Returns:
 *   0 on Error, 1 on success.
 */

return external_call(global.MADX9_HookEnable, argument0);
