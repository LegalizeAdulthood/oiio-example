#include <mandel/iterate.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>

using namespace testing;

TEST(TestIterate, insufficientOptions)
{
    std::ostringstream err;

    const int result{iterate::main({}, err, {})};

    EXPECT_EQ(1, result);
    EXPECT_NE(std::string::npos, err.str().find("Insufficient arguments"));
}

TEST(TestIterate, callsRenderer)
{
    std::ostringstream err;
    const mandel::OrbitRegion region{mandel::Complex(-1.5,-1.5), mandel::Complex(1.5,1.5)};
    const int width{640};
    const int height{480};
    const int maxIter{256};
    testing::MockFunction<mandel::Renderer> renderer;
    std::vector<mandel::OrbitResult> image;
    EXPECT_CALL(renderer, Call(region, maxIter, width, height)).WillOnce(Return(image));

    const int result{iterate::main({"iterate", "-1.5,-1.5", "1.5,1.5"}, err, renderer.AsStdFunction())};

    EXPECT_EQ(0, result);
    EXPECT_TRUE(err.str().empty());
}
