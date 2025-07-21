#include "diskusage.h"
#include <gtest/gtest.h>
#include <filesystem>

TEST(DiskUsageTest, ParseSampleFile) {
    std::filesystem::path src_dir = std::filesystem::path(__FILE__).parent_path();
    auto path = src_dir / "sample_disk_usage.txt";
    auto du = parseDiskUsageFile(path.string());
    ASSERT_EQ(du.total_kb, 1000u);
    ASSERT_EQ(du.used_kb, 400u);
    ASSERT_EQ(du.available_kb, 600u);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
