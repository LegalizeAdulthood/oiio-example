#include <mandel/mandel.h>

namespace mandel
{

OIIO::ImageSpec get_iter_spec(int width, int height)
{
    OIIO::ImageSpec spec;
    spec.width = width;
    spec.height = height;
    spec.nchannels = 2;
    spec.channelformats.assign(
        {OIIO::TypeDesc(OIIO::TypeDesc::DOUBLE, OIIO::TypeDesc::VEC2), OIIO::TypeDesc(OIIO::TypeDesc::UINT32)});
    spec.channelnames.assign({"lastZ", "iterationCount"});
    spec.attribute("oiio:ColorSpace", "scene_linear");
    return spec;
}

OrbitResult iterate(const std::complex<double> &c, std::uint32_t maxIter)
{
    OrbitResult result;
    result.lastZ = c;
    result.count = 1;

    while (std::abs(result.lastZ) < 4.0 && result.count < maxIter)
    {
        result.lastZ = result.lastZ*result.lastZ + c;
        ++result.count;
    }
    return result;
}

} // namespace mandel
