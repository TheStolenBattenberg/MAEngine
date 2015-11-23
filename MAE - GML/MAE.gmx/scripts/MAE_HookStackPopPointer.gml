///MAE_HookStackPopPointer()

/**
 * Description:
 *   Pops a pointer from the stack. Must be freed by MAE_FreePointer
 *
 * Arguments:
 *   [N/A]
 *
 * Returns:
 *   A null pointer on error, otherwise a valid pointer
 */

return external_call(global.MADX9_HookStackPopPointer);
