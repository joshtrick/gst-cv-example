#include "my_app/utils.h"

int bus_cb(GstBus *bus, GstMessage *msg, gpointer user_data)
{
  CustomData *data = (CustomData *) user_data;
  GMainLoop *loop = data->loop;
  GstElement *pipeline = data->pipeline;
  gboolean loop_video = data->loop_video;
  switch (GST_MESSAGE_TYPE(msg))
  {
    case GST_MESSAGE_EOS:
    {
      g_print("End of stream\n");
      if (!loop_video)
      {
        g_main_loop_quit(loop);
      } else {
        gst_element_set_state(pipeline, GST_STATE_NULL);
        gst_element_set_state(pipeline, GST_STATE_PLAYING);
      }
      break;
    }

    case GST_MESSAGE_ERROR:
    {
      gchar *debug;
      GError *err;
      gst_message_parse_error(msg, &err, &debug);
      g_free(debug);
      g_printerr("Error: %s\n", err->message);
      g_error_free(err);

      g_main_loop_quit(loop);
      break;
    }

    default:
      break;
  }

  return 1;
}

void on_pad_added(GstElement *element, GstPad *pad, gpointer user_data)
{
  CustomData *data = (CustomData *) user_data;
  GstPad *sinkpad;
  GstElement *convert = data->convert;

  sinkpad = gst_element_get_static_pad(convert, "sink");

  gst_pad_link(pad, sinkpad);

  gst_object_unref(sinkpad);
}

