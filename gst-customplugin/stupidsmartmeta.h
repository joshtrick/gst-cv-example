#ifndef _STUPID_SMART_META_H_
#define _STUPID_SMART_META_H_

#include <gst/gst.h>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

G_BEGIN_DECLS

#define STUPID_SMART_META_API_TYPE (stupid_smart_meta_api_get_type())
#define STUPID_SMART_META_INFO (stupid_smart_meta_get_info())

typedef struct _StupidSmartMeta StupidSmartMeta;

struct _StupidSmartMeta
{
  GstMeta   Meta;

  /* FILL ME */
  /* for custom variables */
  int size;
  //std::vector<int> bbox[80];
  int bbox[20][4];
};

GType stupid_smart_meta_api_get_type (void);

const GstMetaInfo *stupid_smart_meta_get_info (void);

#define gst_buffer_get_stupid_smart_meta(b) ((StupidSmartMeta*)gst_buffer_get_meta((b),STUPID_SMART_META_API_TYPE))
#define gst_buffer_add_stupid_smart_meta(b) ((StupidSmartMeta*)gst_buffer_add_meta((b),STUPID_SMART_META_INFO, NULL))

G_END_DECLS

#endif
