#pragma once

#include <functional>
#include <string_view>
#include <vector>

namespace mandel
{

std::vector<std::string_view> args(int argc, char *argv[]);

} // namespace mandel
