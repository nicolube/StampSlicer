#include <core/LayerGanerator.hpp>
#include <iostream>
#include <gtest/gtest.h>

using std::cout;
using std::endl;

using namespace formats;
using namespace core;

TEST(LayoutGeneratorTest, Constructor)
{

    Image image{1440, 2560};
    Image part{500, 500};

    part.fill(0, 0, part.getWidth(), 2, 255);
    part.fill(0, part.getHeight() - 2, part.getWidth(), 2, 255);
    part.fill(0, 0, 2, part.getHeight(), 255);
    part.fill(part.getWidth() - 2, 0, 2, part.getHeight(), 255);
    part.fill(0, 0, 10, 10, 255);

    config::PrinterConfig printerConfig{1440, 2560, 68.04, 120.96, 150};
    config::ResinConfig resinConfig{150, 100, 10, 150, 150, 1.0, 1.0, 0, 0, 5, 0.05};

    LayerGanerator generator(printerConfig, resinConfig, 2);

    generator.add(30, 20, part);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int ret = RUN_ALL_TESTS();
    return ret;
}