#include <mandel/mandel.h>

namespace mandel
{

OIIO::ImageSpec get_iter_spec( int width, int height )
{
    OIIO::ImageSpec spec;
    spec.width = width;
    spec.height = height;
    spec.nchannels = 2;
    spec.channelformats.push_back(OIIO::TypeDesc(OIIO::TypeDesc::FLOAT, OIIO::TypeDesc::VEC2));
    spec.channelformats.push_back(OIIO::TypeDesc(OIIO::TypeDesc::UINT32));
    return spec;
}

} // namespace mandel
