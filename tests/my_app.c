#include <gst/gst.h>
#include <string.h>

#include "version_info/version.h"
#include "utils/common.h"
#include "my_app/utils.h"

#define IMAGE_W 1920
#define IMAGE_H 1080

int main(int argc, char *argv[])
{
  /* Print version */
  g_print("%s (v%s.%s.%s)\n",
          PROJECT_NAME,
          PROJECT_VERSION_MAJOR,
          PROJECT_VERSION_MINOR,
          PROJECT_VERSION_PATCH);

  /* Arguments setup */
  gboolean loop_video = FALSE;
  gchar *uri = "https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm";
  gdouble scale_factor = 1.0;
  guint img_w, img_h;

  GOptionEntry entries[] = {
    {"loop", 'l', 0, G_OPTION_ARG_NONE, &loop_video,
      "loop video or not", NULL},
    {"input", 'i', 0, G_OPTION_ARG_FILENAME, &uri,
      "input video", "FILE LOCATION"},
    {"scale", 's', 0, G_OPTION_ARG_DOUBLE, &scale_factor,
      "scale factor, range: 0~1", "SCALE FACTOR"},
    {NULL}
  };

  /* Initialization */
  if (!initiaize_gst(entries, argc, argv))
  {
    return -1;
  }

  /* Main codes */
  /* Parameters declaration */
  GstBus *bus;
  guint bus_watch_id;
  CustomData data;

  GstElement *stupidfilter, *smartfilter;
  stupidfilter = gst_element_factory_make("stupidfilter", "stupidfilter");
  smartfilter = gst_element_factory_make("smartfilter", "smartfilter");
  if (!stupidfilter || !smartfilter)
  {
    g_print("Cannot find the custom element\n");
    return 0;
  }

  /* Create main loop */
  data.loop = g_main_loop_new(NULL, FALSE);

  /* Create elements */
  data.pipeline = gst_pipeline_new("video-player");
  data.source   = gst_element_factory_make("uridecodebin", "source");
  data.convert  = gst_element_factory_make("videoconvert", "convert");
  data.scale    = gst_element_factory_make("videoscale", "scale");
  data.filter   = gst_element_factory_make("capsfilter", "filter");
  data.sink     = gst_element_factory_make("autovideosink", "sink");
  if (!data.pipeline ||
      !data.source   ||
      !data.convert  ||
      !data.scale    ||
      !data.filter   ||
      !data.sink)
  {
    g_printerr("Failure - Element creation\n");
    return -1;
  }

  data.loop_video = loop_video;

  /* Configure elements */
  img_w = (guint) (IMAGE_W * scale_factor);
  img_h = (guint) (IMAGE_H * scale_factor);
  data.caps = gst_caps_new_simple("video/x-raw",
                                   "width", G_TYPE_INT, img_w,
                                   "height", G_TYPE_INT, img_h,
                                   NULL);
  g_object_set(G_OBJECT(data.filter), "caps", data.caps, NULL);
  gst_caps_unref(data.caps);
  g_object_set(G_OBJECT(data.source), "uri", uri, NULL);

  /* Link elements with "Always" pads */
  gst_bin_add_many(GST_BIN(data.pipeline),
                   data.source,
                   data.convert,
                   data.scale,
                   data.filter,
                   stupidfilter,
                   smartfilter,
                   data.sink,
                   NULL);
  if (gst_element_link_many(data.convert,
                            data.scale,
                            data.filter,
                            stupidfilter,
                            smartfilter,
                            data.sink,
                            NULL) != TRUE)
  {
    g_printerr("Failure - Element linkage\n");
    g_object_unref(data.pipeline);
    return -1;
  }

  /* Link elements without "Always" pads */
  g_signal_connect(data.source, "pad-added", G_CALLBACK(on_pad_added), &data);

  /*Add bus watcher */
  bus = gst_pipeline_get_bus(GST_PIPELINE(data.pipeline));
  bus_watch_id = gst_bus_add_watch(bus, bus_cb, &data);
  gst_object_unref(bus);

  /* Set pipeline to playing mode*/
  gst_element_set_state(data.pipeline, GST_STATE_PLAYING);

  g_main_loop_run(data.loop);

  gst_element_set_state(data.pipeline, GST_STATE_NULL);
  gst_object_unref(data.pipeline);
  g_source_remove(bus_watch_id);
  g_main_loop_unref(data.loop);

  return 0;
}

