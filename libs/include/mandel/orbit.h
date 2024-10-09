#pragma once

#include <OpenImageIO/imageio.h>

#include <complex>
#include <cstdint>
#include <functional>
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

inline bool operator==(const OrbitResult &lhs, const OrbitResult &rhs)
{
    return lhs.lastZ == rhs.lastZ //
        && lhs.count == rhs.count;
}
inline bool operator!=(const OrbitResult &lhs, const OrbitResult &rhs)
{
    return !(lhs == rhs);
}

struct OrbitRegion
{
    Complex lowerLeft;
    Complex upperRight;
};

inline bool operator==(const OrbitRegion &lhs, const OrbitRegion &rhs)
{
    return lhs.lowerLeft == rhs.lowerLeft //
        && lhs.upperRight == rhs.upperRight;
}
inline bool operator!=(const OrbitRegion &lhs, const OrbitRegion &rhs)
{
    return !(lhs == rhs);
}

using IteratedRegion = std::vector<OrbitResult>;

using Renderer = std::function<IteratedRegion(const OrbitRegion &region, Count maxIter, int width, int height)>;

} // namespace mandel
