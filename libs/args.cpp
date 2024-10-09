#include <mandel/args.h>

namespace mandel
{

std::vector<std::string_view> args( int argc, char *argv[])
{
    std::vector<std::string_view> result;
    result.reserve(argc);
    for (int i = 0; i < argc; ++i)
    {
        result.emplace_back(argv[i]);
    }

    return result;
}

} // namespace mandel
