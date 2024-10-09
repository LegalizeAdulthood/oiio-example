#pragma once

#include <mandel/orbit.h>

#include <ostream>
#include <string_view>
#include <vector>

namespace iterate
{

int main(const std::vector<std::string_view> &args, std::ostream &err, mandel::Renderer iterator);

} // namespace iterate
