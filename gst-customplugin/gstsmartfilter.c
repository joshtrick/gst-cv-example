#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gst/gst.h>
#include <gst/base/gstbasetransform.h>
#include "gstsmartfilter.h"
#include "stupidsmartmeta.h"

GST_DEBUG_CATEGORY_STATIC (gst_smartfilter_debug_category);
#define GST_CAT_DEFAULT gst_smartfilter_debug_category

/* prototypes */


static void gst_smartfilter_set_property (GObject * object,
    guint property_id, const GValue * value, GParamSpec * pspec);
static void gst_smartfilter_get_property (GObject * object,
    guint property_id, GValue * value, GParamSpec * pspec);

static gboolean gst_smartfilter_set_caps (GstBaseTransform * trans,
    GstCaps * incaps, GstCaps * outcaps);
static gboolean gst_smartfilter_start (GstBaseTransform * trans);
static gboolean gst_smartfilter_stop (GstBaseTransform * trans);
static GstFlowReturn gst_smartfilter_transform_ip (GstBaseTransform * trans,
    GstBuffer * buf);

enum
{
  PROP_0
};

/* pad templates */

static GstStaticPadTemplate gst_smartfilter_src_template =
GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("ANY")
    );

static GstStaticPadTemplate gst_smartfilter_sink_template =
GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("ANY")
    );


/* class initialization */

G_DEFINE_TYPE_WITH_CODE (GstSmartFilter, gst_smartfilter,
    GST_TYPE_BASE_TRANSFORM,
    GST_DEBUG_CATEGORY_INIT (gst_smartfilter_debug_category, "smartfilter", 0,
        "debug category for smartfilter element"));

static void
gst_smartfilter_class_init (GstSmartFilterClass * klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  GstBaseTransformClass *base_transform_class =
      GST_BASE_TRANSFORM_CLASS (klass);

  /* Setting up pads and setting metadata should be moved to
     base_class_init if you intend to subclass this class. */
  gst_element_class_add_static_pad_template (GST_ELEMENT_CLASS (klass),
      &gst_smartfilter_src_template);
  gst_element_class_add_static_pad_template (GST_ELEMENT_CLASS (klass),
      &gst_smartfilter_sink_template);

  gst_element_class_set_static_metadata (GST_ELEMENT_CLASS (klass),
      "FIXME Long name", "Generic", "FIXME Description",
      "FIXME <fixme@example.com>");

  gobject_class->set_property = gst_smartfilter_set_property;
  gobject_class->get_property = gst_smartfilter_get_property;
  base_transform_class->set_caps = GST_DEBUG_FUNCPTR (gst_smartfilter_set_caps);
  base_transform_class->start = GST_DEBUG_FUNCPTR (gst_smartfilter_start);
  base_transform_class->stop = GST_DEBUG_FUNCPTR (gst_smartfilter_stop);
  base_transform_class->transform_ip =
      GST_DEBUG_FUNCPTR (gst_smartfilter_transform_ip);

}

static void
gst_smartfilter_init (GstSmartFilter * smartfilter)
{
}

void
gst_smartfilter_set_property (GObject * object, guint property_id,
    const GValue * value, GParamSpec * pspec)
{
  GstSmartFilter *smartfilter = GST_SMARTFILTER (object);

  GST_DEBUG_OBJECT (smartfilter, "set_property");

  switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

void
gst_smartfilter_get_property (GObject * object, guint property_id,
    GValue * value, GParamSpec * pspec)
{
  GstSmartFilter *smartfilter = GST_SMARTFILTER (object);

  GST_DEBUG_OBJECT (smartfilter, "get_property");

  switch (property_id) {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}

static gboolean
gst_smartfilter_set_caps (GstBaseTransform * trans, GstCaps * incaps,
    GstCaps * outcaps)
{
  GstSmartFilter *smartfilter = GST_SMARTFILTER (trans);

  GST_DEBUG_OBJECT (smartfilter, "set_caps");

  return TRUE;
}

/* states */
static gboolean
gst_smartfilter_start (GstBaseTransform * trans)
{
  GstSmartFilter *smartfilter = GST_SMARTFILTER (trans);

  GST_DEBUG_OBJECT (smartfilter, "start");

  return TRUE;
}

static gboolean
gst_smartfilter_stop (GstBaseTransform * trans)
{
  GstSmartFilter *smartfilter = GST_SMARTFILTER (trans);

  GST_DEBUG_OBJECT (smartfilter, "stop");

  return TRUE;
}

/* sink and src pad event handlers */
static GstFlowReturn
gst_smartfilter_transform_ip (GstBaseTransform * trans, GstBuffer * buf)
{
  GstSmartFilter *smartfilter = GST_SMARTFILTER (trans);

  GST_DEBUG_OBJECT (smartfilter, "transform_ip");

  StupidSmartMeta *meta;
  GstMapInfo in_map_info;
  memset (&in_map_info, 0, sizeof (in_map_info));

  GstPad *pad = NULL;
  GstCaps *caps = NULL;
  GstStructure *str;
  gint width = 0;
  gint height = 0;
  pad = gst_element_get_static_pad ((GstElement *) smartfilter, "sink");
  caps = gst_pad_get_current_caps (pad);
  str = gst_caps_get_structure (caps, 0);
  gst_structure_get_int (str, "height", &height);
  gst_structure_get_int (str, "width", &width);

  gst_caps_unref (caps);
  gst_object_unref (pad);



  if (!gst_buffer_map (buf, &in_map_info, GST_MAP_READ))
  {
    g_printerr("Error: Failed to map gst buffer\n");
    return GST_FLOW_ERROR;
  }

  meta = gst_buffer_get_stupid_smart_meta (buf);
  if (meta != NULL)
  {
    cv::Mat frame(cv::Size(width, height), CV_8UC4, (char *) in_map_info.data, cv::Mat::AUTO_STEP);
    for (int i = 0; i < meta->size; i++)
    {
      cv::rectangle(frame,
                    cv::Point(meta->bbox[i][0], meta->bbox[i][1]),
                    cv::Point(meta->bbox[i][2], meta->bbox[i][3]),
                    cv::Scalar(0, 255, 0), 2, 8, 0);
    }
    //cv::rectangle(frame,
    //              cv::Point(meta->x1, meta->y1),
    //              cv::Point(meta->x2, meta->y2),
    //              cv::Scalar(0, 255, 0), 2, 8, 0);
  } else {
    g_print("No valid metadata\n");
  }

  gst_buffer_unmap (buf, &in_map_info);

  return GST_FLOW_OK;
}

static gboolean
plugin_init (GstPlugin * plugin)
{

  /* FIXME Remember to set the rank if it's an element that is meant
     to be autoplugged by decodebin. */
  return gst_element_register (plugin, "smartfilter", GST_RANK_NONE,
      GST_TYPE_SMARTFILTER);
}

/* FIXME: these are normally defined by the GStreamer build system.
   If you are creating an element to be included in gst-plugins-*,
   remove these, as they're always defined.  Otherwise, edit as
   appropriate for your external plugin package. */
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
    smartfilter,
    "FIXME plugin description",
    plugin_init, VERSION, "LGPL", PACKAGE_NAME, GST_PACKAGE_ORIGIN)
