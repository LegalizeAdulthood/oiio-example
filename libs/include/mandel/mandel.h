#pragma once

#include <OpenImageIO/imageio.h>

namespace mandel
{

OIIO::ImageSpec get_iter_spec( int width, int height );

} // namespace mandel
