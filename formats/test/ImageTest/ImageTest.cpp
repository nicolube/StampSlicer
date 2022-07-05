#include <formats/Image.hpp>
#include <iostream>
#include <gtest/gtest.h>
#include <bitmap_image.hpp>

using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::streampos;

using namespace formats;

TEST(Image, Constructor)
{

    Image image{720, 512};
    for (size_t x = 0; x < 720; x++)
    {
        for (size_t y = 0; y < 512; y++)
        {
            ASSERT_EQ(image.getPixel(x, y), 0);
        }
    }
}

TEST(Image, SetPixel)
{

    Image image1{720, 512};
    image1.setPixel(10, 10, 123);

    ASSERT_EQ(image1.getPixel(10, 10), 123);
}

TEST(Image, Fill)
{

    Image image1{720, 512};
    image1.fill(10, 10, 30, 30, 123);

    for (size_t x = 0; x < 720; x++)
    {
        for (size_t y = 0; y < 512; y++)
        {
            if (x - 10 < 30 && y - 10 < 30)
            {
                ASSERT_EQ(image1.getPixel(x, y), 123) << "Error on x: " << x << ", y: " << y;
            }
            else
            {
                ASSERT_EQ(image1.getPixel(x, y), 0) << "Error on x: " << x << ", y: " << y;
            }
        }
    }
}

TEST(Image, Copy)
{

    Image image1{720, 512};
    for (size_t pos = 0; pos < 512; pos++)
    {
        image1.setPixel(pos, pos, 123);
    }

    Image image2(image1);

    for (size_t i = 0; i < 720 * 512; i++)
    {
        ASSERT_EQ(image1.getBitmap()[i], image2.getBitmap()[i]) << "Image copy failed";
    }

    image2 = image1;
    for (size_t i = 0; i < 720 * 512; i++)
    {
        ASSERT_EQ(image1.getBitmap()[i], image2.getBitmap()[i]) << "Image copy failed: x: " 
        << i % image1.getWidth()
        << ", y: " << i / image1.getHeight();;
    }
    image2 = image2;
    for (size_t i = 0; i < 720 * 512; i++)
    {
        ASSERT_EQ(image1.getBitmap()[i], image2.getBitmap()[i]) << "Image copy failed: x: " 
        << i % image1.getWidth()
        << ", y: " << i / image1.getHeight();;
    }
}

TEST(Image, CopyImage)
{

    Image image1{100, 100};

    Image image2{30, 30};

    for (size_t i = 0; i < 30; i++)
    {
        image2.setPixel(i, i, 1);
        image2.setPixel(29 - i, i, 1);
    }

    image1.copy(30, 30, &image2);

    for (size_t x = 0; x < 100; x++)
    {
        for (size_t y = 0; y < 100; y++)
        {
            if (x >= 0 && y >= 0 && x - 30 < 30 && y - 30 < 30)
            {
                ASSERT_EQ(image1.getPixel(x, y), image2.getPixel(x - 30, y - 30))
                    << "Error on x: " << x << ", y: " << y;
            }
            else
            {
                ASSERT_EQ(image1.getPixel(x, y), 0)
                    << "Error on x: " << x << ", y: " << y;
            }
        }
    }
}

TEST(Image, Padding)
{
    Image image{200, 200};

    for (size_t i = 0; i < 200; i++)
    {
        image.setPixel(i, i, 255);
        image.setPixel(199 - i, i, 255);
    }
    image.padding(1);
    image.padding(3);
    image.padding(-1);
    image.padding(-3);
}

TEST(Image, WriteToBitmap)
{
    Image image{200, 200};

    for (size_t i = 0; i < 200; i++)
    {
        image.setPixel(i, i, 255);
        image.setPixel(199 - i, i, 255);
    }

    bitmap_image bmpImage = image.toBitmapImage();
}



int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int ret = RUN_ALL_TESTS();
    return ret;
}