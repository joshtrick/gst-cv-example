/* GStreamer
 * Copyright (C) 2020 FIXME <fixme@example.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef _GST_STUPIDFILTER_H_
#define _GST_STUPIDFILTER_H_

#include <gst/base/gstbasetransform.h>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

G_BEGIN_DECLS

#define GST_TYPE_STUPIDFILTER   (gst_stupidfilter_get_type())
#define GST_STUPIDFILTER(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_STUPIDFILTER,GstStupidFilter))
#define GST_STUPIDFILTER_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_STUPIDFILTER,GstStupidFilterClass))
#define GST_IS_STUPIDFILTER(obj)   (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_STUPIDFILTER))
#define GST_IS_STUPIDFILTER_CLASS(obj)   (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_STUPIDFILTER))

typedef struct _GstStupidFilter GstStupidFilter;
typedef struct _GstStupidFilterClass GstStupidFilterClass;

struct _GstStupidFilter
{
  GstBaseTransform base_stupidfilter;
  cv::CascadeClassifier face_cascade;

};

struct _GstStupidFilterClass
{
  GstBaseTransformClass base_stupidfilter_class;
};

GType gst_stupidfilter_get_type (void);

G_END_DECLS

#endif
