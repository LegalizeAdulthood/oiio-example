#pragma once

#include <mandel/orbit.h>

#include <functional>
#include <ostream>
#include <string_view>
#include <vector>

namespace iterate
{

using Writer = std::function<int(const mandel::IteratedRegion &, std::string_view filename)>;

int main(const std::vector<std::string_view> &args, std::ostream &err, mandel::Renderer iterator, Writer writer);

} // namespace iterate
