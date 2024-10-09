#include <mandel/args.h>
#include <mandel/iterate.h>
#include <mandel/mandel.h>

#include <OpenImageIO/imageio.h>

#include <iostream>

int main(int argc, char *argv[])
{
    return iterate::main(mandel::args(argc, argv), std::cerr, mandel::render,
        [](const mandel::IteratedRegion &result, std::string_view file) {
            std::unique_ptr out{OIIO::ImageOutput::create(file)};
            if (!out)
            {
                return 1;
            }
            const OIIO::ImageSpec spec{mandel::get_iter_spec(640, 480)};
            out->open(std::string{file}, spec);
            out->write_image(OIIO::TypeUnknown, result.data());
            return 0;
        });
}
