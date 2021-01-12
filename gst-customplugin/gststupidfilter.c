#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>
#include <gst/base/gstbasetransform.h>
#include <gst/video/gstvideometa.h>
#include <stdlib.h>
#include <vector>
#include "gststupidfilter.h"
#include "stupidsmartmeta.h"

GST_DEBUG_CATEGORY_STATIC (gst_stupidfilter_debug_category);
#define GST_CAT_DEFAULT gst_stupidfilter_debug_category

enum
{
  PROP_0
};

/* pad templates */
static GstStaticPadTemplate gst_stupidfilter_src_template =
GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("ANY")
    );

static GstStaticPadTemplate gst_stupidfilter_sink_template =
GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("ANY")
    );

/* prototypes */
static void gst_stupidfilter_set_property (GObject * object,
    guint property_id, const GValue * value, GParamSpec * pspec);
static void gst_stupidfilter_get_property (GObject * object,
    guint property_id, GValue * value, GParamSpec * pspec);

static gboolean gst_stupidfilter_set_caps (GstBaseTransform * trans,
    GstCaps * incaps, GstCaps * outcaps);
static gboolean gst_stupidfilter_start (GstBaseTransform * trans);
static gboolean gst_stupidfilter_stop (GstBaseTransform * trans);
static GstFlowReturn gst_stupidfilter_transform_ip (GstBaseTransform * trans,
    GstBuffer * buf);

/* class initialization */
G_DEFINE_TYPE_WITH_CODE (GstStupidFilter, gst_stupidfilter,
    GST_TYPE_BASE_TRANSFORM,
    GST_DEBUG_CATEGORY_INIT (gst_stupidfilter_debug_category, "stupidfilter", 0,
        "debug category for stupidfilter element"));

static void
gst_stupidfilter_class_init (GstStupidFilterClass * klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  GstBaseTransformClass *base_transform_class =
      GST_BASE_TRANSFORM_CLASS (klass);

  /* Setting up pads and setting metadata should be moved to
     base_class_init if you intend to subclass this class. */
  gst_element_class_add_static_pad_template (GST_ELEMENT_CLASS (klass),
      &gst_stupidfilter_src_template);
  gst_element_class_add_static_pad_template (GST_ELEMENT_CLASS (klass),
      &gst_stupidfilter_sink_template);

  gst_element_class_set_static_metadata (GST_ELEMENT_CLASS (klass),
      "FIXME Long name", "Generic", "FIXME Description",
      "FIXME <fixme@example.com>");

  gobject_class->set_property = gst_stupidfilter_set_property;
  gobject_class->get_property = gst_stupidfilter_get_property;
  base_transform_class->set_caps =
      GST_DEBUG_FUNCPTR (gst_stupidfilter_set_caps);
  base_transform_class->start = GST_DEBUG_FUNCPTR (gst_stupidfilter_start);
  base_transform_class->stop = GST_DEBUG_FUNCPTR (gst_stupidfilter_stop);
  base_transform_class->transform_ip =
      GST_DEBUG_FUNCPTR (gst_stupidfilter_transform_ip);

}

static void
gst_stupidfilter_init (GstStupidFilter * stupidfilter)
{
  if (!stupidfilter->face_cascade.load("/home/josh/workspace/projects/gst-customplugin-example/data/haarcascade_frontalface_default.xml"))
  {
    g_print("Model not initialized\n");
  } else {
    g_print("Model initialized\n");
  }
}

void
gst_stupidfilter_set_property (GObject * object, guint property_id,
    const GValue * value, GParamSpec * pspec)
{
  GstStupidFilter *stupidfilter = GST_STUPIDFILTER (object);

  GST_DEBUG_OBJECT (stupidfilter, "set_property");

  switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

void
gst_stupidfilter_get_property (GObject * object, guint property_id,
    GValue * value, GParamSpec * pspec)
{
  GstStupidFilter *stupidfilter = GST_STUPIDFILTER (object);

  GST_DEBUG_OBJECT (stupidfilter, "get_property");

  switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

static gboolean
gst_stupidfilter_set_caps (GstBaseTransform * trans, GstCaps * incaps,
    GstCaps * outcaps)
{
  GstStupidFilter *stupidfilter = GST_STUPIDFILTER (trans);

  GST_DEBUG_OBJECT (stupidfilter, "set_caps");

  return TRUE;
}

/* decide allocation query for output buffers */

/* transform size */

/* states */
static gboolean
gst_stupidfilter_start (GstBaseTransform * trans)
{
  GstStupidFilter *stupidfilter = GST_STUPIDFILTER (trans);

  GST_DEBUG_OBJECT (stupidfilter, "start");

  return TRUE;
}

static gboolean
gst_stupidfilter_stop (GstBaseTransform * trans)
{
  GstStupidFilter *stupidfilter = GST_STUPIDFILTER (trans);

  GST_DEBUG_OBJECT (stupidfilter, "stop");

  return TRUE;
}

/* sink and src pad event handlers */

/* metadata */

/* transform */
static GstFlowReturn
gst_stupidfilter_transform_ip (GstBaseTransform * trans, GstBuffer * buf)
{
  GstStupidFilter *stupidfilter = GST_STUPIDFILTER (trans);

  GST_DEBUG_OBJECT (stupidfilter, "transform_ip");

  StupidSmartMeta *meta;
  GstMapInfo in_map_info;
  memset (&in_map_info, 0, sizeof (in_map_info));

  meta = gst_buffer_add_stupid_smart_meta (buf);
  std::vector<cv::Rect> faces;
  if (!gst_buffer_map (buf, &in_map_info, GST_MAP_READ))
  {
    g_printerr("Error: Failed to map gst buffer\n");
    return GST_FLOW_ERROR;
  }
  GstPad *pad = NULL;
  GstCaps *caps = NULL;
  GstStructure *str;
  gint width = 0;
  gint height = 0;
  pad = gst_element_get_static_pad ((GstElement *) stupidfilter, "sink");
  caps = gst_pad_get_current_caps (pad);
  str = gst_caps_get_structure (caps, 0);
  gst_structure_get_int (str, "height", &height);
  gst_structure_get_int (str, "width", &width);

  gst_caps_unref (caps);
  gst_object_unref (pad);

  cv::Mat frame(cv::Size(width, height), CV_8UC4, (char *) in_map_info.data, cv::Mat::AUTO_STEP);
  stupidfilter->face_cascade.detectMultiScale(frame, faces, 1.1, 10);
  if (faces.size() <= 0)
  {
    meta->size = faces.size();
  } else {
    meta->size = 20;
  }
  for (int i = 0; i < meta->size; i++)
  {
    meta->bbox[i][0] = faces[i].x;
    meta->bbox[i][1] = faces[i].y;
    meta->bbox[i][2] = faces[i].x + faces[i].width;
    meta->bbox[i][3] = faces[i].y + faces[i].height;
  }

  gst_buffer_unmap (buf, &in_map_info);
  return GST_FLOW_OK;
}

/* register */
static gboolean
plugin_init (GstPlugin * plugin)
{

  return gst_element_register (plugin, "stupidfilter", GST_RANK_NONE,
      GST_TYPE_STUPIDFILTER);
}

#ifndef VERSION
#define VERSION "0.0.FIXME"
#endif
#ifndef PACKAGE
#define PACKAGE "FIXME_package"
#endif
#ifndef PACKAGE_NAME
#define PACKAGE_NAME "FIXME_package_name"
#endif
#ifndef GST_PACKAGE_ORIGIN
#define GST_PACKAGE_ORIGIN "http://FIXME.org/"
#endif

GST_PLUGIN_DEFINE (GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    stupidfilter,
    "FIXME plugin description",
    plugin_init, VERSION, "LGPL", PACKAGE_NAME, GST_PACKAGE_ORIGIN)
