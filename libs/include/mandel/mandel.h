#pragma once

#include <OpenImageIO/imageio.h>

#include <complex>
#include <cstdint>
#include <vector>

namespace mandel
{

using Complex = std::complex<double>;
using Count = std::uint32_t;

struct OrbitResult
{
    Complex lastZ;
    Count count;
};

struct OrbitRegion
{
    Complex lowerLeft;
    Complex upperRight;
};

OIIO::ImageSpec get_iter_spec(int width, int height);

OrbitResult iterate(const Complex &c, Count maxIter);

std::vector<mandel::OrbitResult> iterate(const OrbitRegion & region, Count maxIter, int width, int height);

} // namespace mandel
