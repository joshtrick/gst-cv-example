#include "stupidsmartmeta.h"

static gboolean
stupid_smart_meta_transform (GstBuffer * dest, GstMeta * meta,
                             GstBuffer * buffer, GQuark type, gpointer data)
{
  /* FILL ME */
  /* for meta transform */
  return TRUE;
}

GType
stupid_smart_meta_api_get_type (void)
{
  static volatile GType type = 0;
  static const gchar *tags[] =
  {
    "FILL",
    "ME",
    NULL
  };

  if (g_once_init_enter (&type))
  {
    GType _type = gst_meta_api_type_register ("StupidSmartMetaAPI", tags);
    g_once_init_leave (&type, _type);
  }
  return type;
}

static gboolean
stupid_smart_meta_init (GstMeta * meta, gpointer params, GstBuffer * buffer)
{
  StupidSmartMeta *emeta = (StupidSmartMeta *) meta;

  /* FILL ME */
  /* for variables initialization */
  emeta->size = 20;
  for (int i = 0; i < emeta->size; i++)
  {
    emeta->bbox[i][0] = 0;
    emeta->bbox[i][1] = 0;
    emeta->bbox[i][2] = 0;
    emeta->bbox[i][3] = 0;
  }
  return TRUE;
}

static void stupid_smart_meta_free (GstMeta *meta, GstBuffer *buffer)
{
  //StupidSmartMeta *emeta = (StupidSmartMeta *) meta;

  /* FILL ME */
  /* for variable release */
}

const GstMetaInfo *
stupid_smart_meta_get_info (void)
{
  static const GstMetaInfo *stupid_smart_meta_info = NULL;

  if (g_once_init_enter ((GstMetaInfo **) & stupid_smart_meta_info))
  {
    const GstMetaInfo *meta = gst_meta_register (STUPID_SMART_META_API_TYPE,
                                                 "StupidSmartMeta",
                                                 sizeof (StupidSmartMeta),
                                                 (GstMetaInitFunction) stupid_smart_meta_init,
                                                 (GstMetaFreeFunction) stupid_smart_meta_free,
                                                 stupid_smart_meta_transform);
    g_once_init_leave ((GstMetaInfo **) & stupid_smart_meta_info,
        (GstMetaInfo *) meta);
  }

  return stupid_smart_meta_info;
}
