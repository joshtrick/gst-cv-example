#include "utils/common.h"

gboolean initiaize_gst(GOptionEntry entries[], int argc, char *argv[])
{
  GOptionContext *ctx;
  GError *err = NULL;

  /* Initialization */
  ctx = g_option_context_new("- Your application");
  g_option_context_add_main_entries(ctx, entries, NULL);
  g_option_context_add_group(ctx, gst_init_get_option_group());
  if (!g_option_context_parse(ctx, &argc, &argv, &err))
  {
    g_print("Failed to initialize: %s\n", err->message);
    g_clear_error(&err);
    g_option_context_free(ctx);
    return FALSE;
  }
  g_option_context_free(ctx);
  return TRUE;
}
