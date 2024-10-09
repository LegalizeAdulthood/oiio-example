#include <mandel/args.h>

#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <string>

TEST(TestArgs, empty)
{
    EXPECT_EQ(std::vector<std::string_view>(), mandel::args(0, nullptr));
}

TEST(TestArgs, values)
{
    std::vector<std::string> values{"one", "two", "three"};
    std::vector<char *> args;
    std::transform(values.begin(), values.end(), std::back_inserter(args), [](std::string &text) { return text.data(); });

    const std::vector<std::string_view> result{mandel::args(static_cast<int>(args.size()), args.data())};

    ASSERT_EQ(values.size(), result.size());
    for (std::size_t i = 0; i < result.size(); ++i)
    {
        EXPECT_EQ(values[i], result[i]);
    }
}
