#include <mandel/mandel.h>

#include <gtest/gtest.h>

using namespace testing;

constexpr const char *const ARBITRARY_TIFF_FILE{"tmp.tif"};
constexpr const char *const ARBITRARY_EXR_FILE{"tmp.exr"};

TEST(TestMandel, getImageSpec)
{
    constexpr int width{640};
    constexpr int height{480};

    const OIIO::ImageSpec result{mandel::get_iter_spec(width, height)};

    EXPECT_EQ(width, result.width);
    EXPECT_EQ(height, result.height);
    EXPECT_EQ(3, result.nchannels);
    ASSERT_EQ(3U, result.channelformats.size());
    EXPECT_EQ(OIIO::TypeDesc::FLOAT, result.channelformats[0]);
    EXPECT_EQ(OIIO::TypeDesc::FLOAT, result.channelformats[1]);
    EXPECT_EQ(OIIO::TypeDesc::UINT32, result.channelformats[2]);
    ASSERT_EQ(3U, result.channelnames.size());
    EXPECT_EQ("0.lastZReal", result.channelnames[0]);
    EXPECT_EQ("1.lastZImag", result.channelnames[1]);
    EXPECT_EQ("2.iterationCount", result.channelnames[2]);
    EXPECT_EQ("scene_linear", result.get_string_attribute("oiio:ColorSpace"));
}

TEST(TestMandel, iterateToMax)
{
    mandel::OrbitResult result{mandel::mandelbrot(mandel::Complex{-1.5, 0}, 256)};

    EXPECT_NE(mandel::Complex(), result.lastZ);
    EXPECT_EQ(256, result.count);
}

TEST(TestMandel, exrSupportsChannelFormats)
{
    std::unique_ptr<OIIO::ImageOutput> image{OIIO::ImageOutput::create(ARBITRARY_EXR_FILE)};
    ASSERT_TRUE(image);

    const bool result{image->supports("channelformats") != 0};

    EXPECT_TRUE(result);
}

TEST(TestMandel, exrSupportsArbitraryMetadata)
{
    std::unique_ptr<OIIO::ImageOutput> image{OIIO::ImageOutput::create(ARBITRARY_EXR_FILE)};
    ASSERT_TRUE(image);

    const bool result{image->supports("arbitrary_metadata") != 0};

    EXPECT_TRUE(result);
}

TEST(TestMandel, openExrFromSpec)
{
    std::unique_ptr<OIIO::ImageOutput> image{OIIO::ImageOutput::create(ARBITRARY_EXR_FILE)};
    ASSERT_TRUE(image);

    const bool result{image->open(ARBITRARY_EXR_FILE, mandel::get_iter_spec(640, 480))};

    EXPECT_TRUE(result);
}

TEST(TestMandel, tiffSupportsChannelFormatsFails)
{
    std::unique_ptr<OIIO::ImageOutput> image{OIIO::ImageOutput::create(ARBITRARY_TIFF_FILE)};
    ASSERT_TRUE(image);

    const bool result{image->supports("channelformats") != 0};

    EXPECT_FALSE(result);
}

TEST(TestMandel, openTiffFromSpecFails)
{
    std::unique_ptr<OIIO::ImageOutput> image{OIIO::ImageOutput::create(ARBITRARY_TIFF_FILE)};
    ASSERT_TRUE(image);

    const bool result{image->open(ARBITRARY_TIFF_FILE, mandel::get_iter_spec(640, 480))};

    EXPECT_FALSE(result);
}

TEST(TestMandel, iterateRegion)
{
    const mandel::OrbitRegion region{mandel::Complex{-1.5, -1.5}, mandel::Complex{1.5, 1.5}};
    const mandel::Count maxIter{256};
    const int width{8};
    const int height{8};

    std::vector<mandel::OrbitResult> result{render(region, maxIter, width, height)};

    EXPECT_EQ(static_cast<std::size_t>(width*height), result.size());
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            ASSERT_NE(0, result[y * width + x].count)
                << "[" << x << "," << y << " of " << width << "," << height << "] count is zero";
        }
    }
}
