#include <mandel/iterate.h>

#include <OpenImageIO/imageio.h>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <sstream>
#include <stdexcept>

using namespace testing;

class MockImageOutput : public StrictMock<OIIO::ImageOutput>
{
public:
    ~MockImageOutput() override = default;

    MOCK_METHOD(bool, close, (), (override));
    MOCK_METHOD(bool, copy_image, (OIIO::ImageInput *), (override));
    MOCK_METHOD(const char *, format_name, (), (const, override));
    MOCK_METHOD(bool, open, (const std::string &, const OIIO::ImageSpec &, OpenMode), (override));
    MOCK_METHOD(bool, open, (const std::string &, int, const OIIO::ImageSpec *), (override));
    virtual int send_to_output(const char *, ...) override
    {
        return 0;
    }
    MOCK_METHOD(bool, set_ioproxy, (OIIO::Filesystem::IOProxy *), (override));
    MOCK_METHOD(bool, set_thumbnail, (const OIIO::ImageBuf &), (override));
    MOCK_METHOD(int, supports, (OIIO::string_view), (const, override));
    MOCK_METHOD(bool, write_deep_image, (const OIIO::DeepData &), (override));
    MOCK_METHOD(bool, write_deep_scanlines, (int, int, int, const OIIO::DeepData &), (override));
    MOCK_METHOD(bool, write_deep_tiles, (int, int, int, int, int, int, const OIIO::DeepData &), (override));
    MOCK_METHOD(bool, write_image,
        (OIIO::TypeDesc, const void *, OIIO::stride_t, OIIO::stride_t, OIIO::stride_t, OIIO::ProgressCallback, void *),
        (override));
    MOCK_METHOD(bool, write_rectangle,
        (int, int, int, int, int, int, OIIO::TypeDesc, const void *, OIIO::stride_t, OIIO::stride_t, OIIO::stride_t),
        (override));
    MOCK_METHOD(bool, write_scanline, (int, int, OIIO::TypeDesc, const void *, OIIO::stride_t), (override));
    MOCK_METHOD(bool, write_scanlines, (int, int, int, OIIO::TypeDesc, const void *, OIIO::stride_t, OIIO::stride_t),
        (override));
    MOCK_METHOD(bool, write_tile,
        (int, int, int, OIIO::TypeDesc, const void *, OIIO::stride_t, OIIO::stride_t, OIIO::stride_t), (override));
    MOCK_METHOD(bool, write_tiles,
        (int, int, int, int, int, int, OIIO::TypeDesc, const void *, OIIO::stride_t, OIIO::stride_t, OIIO::stride_t),
        (override));
};

TEST(TestIterate, insufficientOptions)
{
    std::ostringstream err;

    const int result{iterate::main({}, err, {}, {})};

    EXPECT_EQ(1, result);
    EXPECT_NE(std::string::npos, err.str().find("Insufficient arguments"));
}

TEST(TestIterate, callsRendererWriter)
{
    std::ostringstream err;
    const mandel::OrbitRegion region{mandel::Complex(-1.5,-1.5), mandel::Complex(1.5,1.5)};
    const int width{640};
    const int height{480};
    const int maxIter{256};
    MockFunction<mandel::Renderer> renderer;
    std::vector<mandel::OrbitResult> image;
    EXPECT_CALL(renderer, Call(region, maxIter, width, height)).WillOnce(Return(image));
    //MockFunction<iterate::Writer> writer;
    //EXPECT_CALL(writer, Call(image, "foo.exr")).WillOnce(Return(0));
    mandel::IteratedRegion actualRegion;
    std::string actualFile;
    bool called{false};

    const int result{iterate::main({"iterate", "-1.5,-1.5", "1.5,1.5", "foo.exr"}, err, renderer.AsStdFunction(),
        [&](const mandel::IteratedRegion &iterRegion, std::string_view file)
        {
            called =true;
            actualRegion = iterRegion;
            actualFile = file;
            return 0;
        })};

    EXPECT_EQ(0, result);
    EXPECT_TRUE(err.str().empty());
    EXPECT_TRUE(called);
    EXPECT_EQ(image, actualRegion);
    EXPECT_EQ("foo.exr", actualFile);
}
