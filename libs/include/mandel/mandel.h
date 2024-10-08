#pragma once

#include <OpenImageIO/imageio.h>

#include <complex>
#include <cstdint>

namespace mandel
{

struct OrbitResult
{
    std::complex<double> lastZ;
    std::uint32_t iterationCount;
};

OIIO::ImageSpec get_iter_spec(int width, int height);

OrbitResult iterate(const std::complex<double> &loc, std::uint32_t maxIter);

} // namespace mandel
