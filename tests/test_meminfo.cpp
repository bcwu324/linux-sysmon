#include "meminfo.h"
#include <gtest/gtest.h>
#include <filesystem>

TEST(MemInfoTest, ParseSampleFile) {
    std::filesystem::path src_dir = std::filesystem::path(__FILE__).parent_path();
    auto path = src_dir / "sample_meminfo.txt";
    auto info = parseMemInfo(path.string());
    ASSERT_EQ(info["MemTotal"], 16384256);
    ASSERT_EQ(info["MemAvailable"], 9876543);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
