#pragma once

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

using Renderer = std::function<std::vector<OrbitResult>(const OrbitRegion &region, Count maxIter, int width, int height)>;

} // namespace mandel
