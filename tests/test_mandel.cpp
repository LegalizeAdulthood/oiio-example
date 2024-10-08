#include <mandel/mandel.h>

#include <gtest/gtest.h>

using namespace testing;

TEST(TestMandel, getImageSpec)
{
    constexpr int width{640};
    constexpr int height{480};

    const OIIO::ImageSpec result{mandel::get_iter_spec(width, height)};

    EXPECT_EQ(width, result.width);
    EXPECT_EQ(height, result.height);
    EXPECT_EQ(2, result.nchannels);
    ASSERT_EQ(2U, result.channelformats.size());
    EXPECT_EQ(OIIO::TypeDesc(OIIO::TypeDesc::DOUBLE, OIIO::TypeDesc::VEC2), result.channelformats[0]);
    EXPECT_EQ(OIIO::TypeDesc(OIIO::TypeDesc::UINT32), result.channelformats[1]);
    ASSERT_EQ(2U, result.channelnames.size());
    EXPECT_EQ("lastZ", result.channelnames[0]);
    EXPECT_EQ("iterationCount", result.channelnames[1]);
}

TEST(TestMandel, iterateToMax)
{
    mandel::OrbitResult result{mandel::iterate(std::complex<double>{-1.5, 0}, 256)};

    EXPECT_NE(std::complex<double>(), result.lastZ);
    EXPECT_EQ(256, result.iterationCount);
}

TEST(TestMandel, openExrFromSpec)
{
    std::unique_ptr<OIIO::ImageOutput> image{OIIO::ImageOutput::create("tmp.exr")};

    const bool result{image->open("tmp.exr", mandel::get_iter_spec(640, 480))};

    EXPECT_TRUE(result);
}

TEST(TestMandel, openTiffFromSpec)
{
    std::unique_ptr<OIIO::ImageOutput> image{OIIO::ImageOutput::create("tmp.tiff")};

    const bool result{image->open("tmp.tiff", mandel::get_iter_spec(640, 480))};

    EXPECT_FALSE(result);
}
