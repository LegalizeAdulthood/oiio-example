#include <mandel/args.h>
#include <mandel/mandel.h>
#include <mandel/orbit.h>

#include <OpenImageIO/imageio.h>

#include <cstdint>
#include <iostream>

namespace
{

void color_iterations(OIIO::ImageInput *in, OIIO::ImageOutput *out)
{
    const OIIO::ImageSpec &spec{in->spec()};
    std::vector<mandel::OrbitResult> in_scanline;
    in_scanline.resize(spec.width);
    std::vector<std::uint8_t> out_scanline;
    out_scanline.resize(spec.width*3);

    for (int y = 0; y < spec.height; ++y)
    {
        std::fill(in_scanline.begin(), in_scanline.end(), mandel::OrbitResult{mandel::Complex(), 0});
        in->read_scanline(y, 0, OIIO::TypeDesc::UNKNOWN, in_scanline.data());
        std::uint8_t *dest{out_scanline.data()};
        for (int x = 0; x < spec.width; ++x)
        {
            const std::uint8_t pixel{static_cast<std::uint8_t>(in_scanline[x].count % 256)};
            *dest = pixel;
            ++dest;
            *dest = pixel;
            ++dest;
            *dest = pixel;
            ++dest;
        }
        out->write_scanline(y, 0, OIIO::TypeDesc::UINT8, out_scanline.data());
    }
}

}

int main(int argc, char *argv[])
{
    const std::vector args{mandel::args(argc, argv)};

    if (args.size() < 2)
    {
        std::cerr << "Insufficient arguments\n"
            "Usage: <in-file> <out-file>\n";
        return 1;
    }

    const OIIO::ImageSpec requested{mandel::get_iter_spec(640, 480)};
    std::unique_ptr in{OIIO::ImageInput::open(std::string{args[1]}, &requested)};
    if (!in)
    {
        std::cerr << "Couldn't open input file " << args[1] << '\n';
        return 2;
    }

    std::unique_ptr out{OIIO::ImageOutput::create(args[2])};
    if (!out)
    {
        std::cerr << "Couldn't create output image from file " << args[2] << '\n';
        return 3;
    }
    const OIIO::ImageSpec &inSpec{in->spec()};
    OIIO::ImageSpec outSpec;
    outSpec.width = inSpec.width;
    outSpec.height = inSpec.height;
    outSpec.format = OIIO::TypeDesc(OIIO::TypeDesc::UINT8);
    outSpec.nchannels = 3;
    if (!out->open(std::string{args[2]}, outSpec))
    {
        std::cerr << "Couldn't create output file " << args[2] << '\n';
        return 4;
    }

    color_iterations(in.get(), out.get());

    return 0;
}
