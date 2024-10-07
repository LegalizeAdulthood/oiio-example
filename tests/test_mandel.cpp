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
    EXPECT_EQ(OIIO::TypeDesc(OIIO::TypeDesc::FLOAT, OIIO::TypeDesc::VEC2), result.channelformats[0]);
    EXPECT_EQ(OIIO::TypeDesc(OIIO::TypeDesc::UINT32), result.channelformats[1]);
}
