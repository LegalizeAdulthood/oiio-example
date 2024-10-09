#pragma once

#include <OpenImageIO/imageio.h>

#include <complex>
#include <cstdint>

namespace mandel
{

using Complex = std::complex<double>;
using Count = std::uint32_t;

struct OrbitResult
{
    Complex lastZ;
    Count count;
};

OIIO::ImageSpec get_iter_spec(int width, int height);

OrbitResult iterate(const Complex &c, Count maxIter);

} // namespace mandel
