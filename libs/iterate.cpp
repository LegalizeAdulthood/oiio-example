#include <mandel/iterate.h>

#include <sstream>

namespace iterate
{

mandel::Complex parse(std::string_view text)
{
    std::istringstream str(text.data());
    double re;
    str >> re;
    char c;
    str >> c;
    double im;
    str >> im;
    return {re, im};
}

int main(const std::vector<std::string_view> &args, std::ostream &err, mandel::Renderer iter, Writer writer)
{
    if (args.size() < 4)
    {
        err << "Insufficient arguments\n"
            "Usage: <ll_real,ll_imag> <ur_real,ur_imag> <file>\n";
        return 1;
    }

    const mandel::OrbitRegion region{parse(args[1]), parse(args[2])};
    const std::vector<mandel::OrbitResult> result{iter(region, 256, 640, 480)};
    return writer(result, args[3]);
}

} // namespace iterate
