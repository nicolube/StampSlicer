#include <formats/cbddlp/FormatCbddlp.hpp>
#include <formats/Image.hpp>
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::streampos;

using namespace formats::cbddlp;

class FormatCbddlpTest : public ::testing::Test
{
public:
    char *fileData;
    size_t size;

protected:
    void SetUp() override
    {
        ifstream file;
        file.open("../../../resources/TestFugure.cbddlp", ios::binary);

        ASSERT_TRUE(file.is_open()) << "Failed to open file ../../../resources/TestFugure.cbddlp";

        // Load file
        file.seekg(0, ios::end);
        streampos end = file.tellg();
        file.seekg(0, ios::beg);
        streampos start = file.tellg();
        size = end - start;
        fileData = new char[size];
        file.read(fileData, size);
        file.close();
    }

    void TearDown() override
    {
        delete[] fileData;
    }
};

TEST_F(FormatCbddlpTest, Size)
{
    ASSERT_EQ(size, 35388926) << "Invalid file size.";
}

TEST_F(FormatCbddlpTest, Content)
{
    FormatCbddlp cbddlpLoader;
    cbddlpLoader.load(fileData, size);
    cbddlp_file_head_t &header = cbddlpLoader.header;

    ASSERT_EQ(header.magic, 0x12fd0019) << "File type is not cbddlp";

    ASSERT_EQ(header.version, 4);
    ASSERT_FLOAT_EQ(header.layer_height_mm, 0.05);
    ASSERT_FLOAT_EQ(header.exposure_s, 15);
    ASSERT_FLOAT_EQ(header.bot_exposure_s, 70);
    ASSERT_FLOAT_EQ(header.light_off_time_s, 0);
    ASSERT_EQ(header.bot_layer_count, 5);
    ASSERT_EQ(header.resolution_x, 1440);
    ASSERT_EQ(header.resolution_y, 2560);

    ASSERT_FLOAT_EQ(header.bed_x_mm, 68.04);
    ASSERT_FLOAT_EQ(header.bed_y_mm, 120.96);
    ASSERT_FLOAT_EQ(header.bed_z_mm, 150);

    ASSERT_EQ(header.layer_table_count, 1177);

    // cout
    //      << "previewOneOffsetAddress: " << header.previewOneOffsetAddress << endl
    //      << "layersDefinitionOffsetAddress: " << header.layersDefinitionOffsetAddress << endl
    //      << "previewTwoOffsetAddress: " << header.previewTwoOffsetAddress << endl;
    // ASSERT_TRUE(false);
}


TEST(Image, EncodeDecode) {

    formats::Image image1{200, 200};

    for (size_t i = 0; i < 200; i++)
    {
        image1.setPixel(i, i, 255);
        image1.setPixel(199 - i, i, 255);
    }
    image1.fill(0, 0, 2, 2, 255);

    u_int encodeLength;
    unsigned char *imageBuffer = FormatCbddlp::encode(&image1, encodeLength);

    formats::Image image2{200, 200};
    FormatCbddlp::decode(imageBuffer, encodeLength, &image2);

    for (size_t i = 0; i < 200 * 200; i++)
    {
        ASSERT_EQ(image1.getBitmap()[i], image2.getBitmap()[i]) 
        << "x: " << i % 200
        << " y: " << i / 200;
    }

    delete[] imageBuffer;
    
}



int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int ret = RUN_ALL_TESTS();
    return ret;
}