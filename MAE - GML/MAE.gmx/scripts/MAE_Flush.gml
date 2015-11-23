///MAE_Flush()

/**
 * Description:
 *   Flushes GameMaker: Studio's drawing buffer. This might be useful when changing
 *   render states using the MAE_SetRenderState function. Requires INIT_FLUSH.
 *
 * Arguments:
 *   [N/A]
 *
 * Returns:
 *   [N/A]
 */

vertex_submit(global.MAE_FlushBuffer, pr_pointlist, -1);

