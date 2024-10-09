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

std::vector<OrbitResult> iterate(const OrbitRegion &region, Count maxIter, int width, int height)
{
    std::vector<OrbitResult> result;
    result.resize(width*height);

    auto it{result.begin()};
    const Complex delta{region.upperRight - region.lowerLeft};
    const double delta_x{delta.real() / width};
    const double delta_y{delta.imag() / height};
    for (int y = 0; y < height; ++y)
    {
        const double imag{region.lowerLeft.imag() + delta_y * y};
        for (int x = 0; x < width; ++x)
        {
            const double real{region.lowerLeft.real() + delta_x * x};
            *it = iterate(Complex{real, imag}, maxIter);
            ++it;
        }
    }

    return result;
}

} // namespace mandel
