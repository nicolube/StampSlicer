#include <core/SvgConverter.hpp>
#include <iostream>
#include <gtest/gtest.h>

using std::cout;
using std::endl;

using namespace formats;
using namespace core;

TEST (SvgConverter, Convert) {
    
    config::PrinterConfig printerConfig{1440, 2560, 68.04, 120.96, 150};

    SvgConverter converter{printerConfig, "test.svg"};
    converter.setHight(60);
    Image img = converter.toImage();
    ASSERT_EQ(img.getWidth(), (int)(60 * printerConfig.getResolutionX() / printerConfig.getBedWidth()));
    ASSERT_EQ(img.getHeight(), (int)(60 * printerConfig.getResolutionY() / printerConfig.getBedLength()));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int ret = RUN_ALL_TESTS();
    return ret;
}