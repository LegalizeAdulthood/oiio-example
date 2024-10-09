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

int main(const std::vector<std::string_view> &args, std::ostream &err, mandel::Renderer iter)
{
    if (args.size() < 3)
    {
        err << "Insufficient arguments\n"
            "Usage: ll_real,ll_imag ur_real,ur_imag file\n";
        return 1;
    }

    const mandel::OrbitRegion region{parse(args[1]), parse(args[2])};
    iter(region, 256, 640, 480);

    return 0;
}

} // namespace iterate
