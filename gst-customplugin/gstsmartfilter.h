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

#ifndef _GST_SMARTFILTER_H_
#define _GST_SMARTFILTER_H_

#include <gst/base/gstbasetransform.h>
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

G_BEGIN_DECLS

#define GST_TYPE_SMARTFILTER   (gst_smartfilter_get_type())
#define GST_SMARTFILTER(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_SMARTFILTER,GstSmartFilter))
#define GST_SMARTFILTER_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_SMARTFILTER,GstSmartFilterClass))
#define GST_IS_SMARTFILTER(obj)   (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_SMARTFILTER))
#define GST_IS_SMARTFILTER_CLASS(obj)   (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_SMARTFILTER))

typedef struct _GstSmartFilter GstSmartFilter;
typedef struct _GstSmartFilterClass GstSmartFilterClass;

struct _GstSmartFilter
{
  GstBaseTransform base_smartfilter;

};

struct _GstSmartFilterClass
{
  GstBaseTransformClass base_smartfilter_class;
};

GType gst_smartfilter_get_type (void);

G_END_DECLS

#endif
