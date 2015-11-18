///MAE_Flush()

/**
 * Description:
 *   Flushes GameMaker: Studio's drawing buffer. This might be useful when changing
 *   render states using the MAE_RenderSetState function
 *
 * Returns:
 *   Nothing.
 */

vertex_submit(global.MAE_FlushBuffer, pr_pointlist, -1);

