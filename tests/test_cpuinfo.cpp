#include "cpuinfo.h"
#include <gtest/gtest.h>
#include <filesystem>

TEST(CpuInfoTest, ParseSampleStat) {
    std::filesystem::path src_dir = std::filesystem::path(__FILE__).parent_path();
    auto path = src_dir / "sample_proc_stat.txt";
    auto usage = getCpuUsageFromFile(path.string());
    ASSERT_NEAR(usage.first, 28.5714, 0.001);
    ASSERT_NEAR(usage.second, 28.5714, 0.001);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
