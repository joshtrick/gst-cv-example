#ifndef UTILS_H
#define UTILS_H

#include <gst/gst.h>
#include <string.h>

typedef struct _CustomData
{
  GMainLoop *loop;
  GstElement *pipeline;
  GstElement *source, *convert, *scale, *filter, *sink;
  GstCaps *caps;
  gboolean loop_video;

} CustomData;


int bus_cb(GstBus *bus, GstMessage *msg, gpointer user_data);
void on_pad_added(GstElement *element, GstPad *pad, gpointer user_data);

#endif //UTILS_H
