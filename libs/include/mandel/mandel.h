#pragma once

#include <mandel/orbit.h>

#include <OpenImageIO/imageio.h>

#include <vector>

namespace mandel
{

OIIO::ImageSpec get_iter_spec(int width, int height);

OrbitResult mandelbrot(const Complex &c, Count maxIter);

std::vector<OrbitResult> render(const OrbitRegion & region, Count maxIter, int width, int height);

} // namespace mandel
