#include <formats/cbddlp/FormatCbddlp.hpp>
#include <formats/config/PrinterConfig.hpp>
#include <formats/config/ResinConfig.hpp>
#include <formats/Image.hpp>
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::streampos;

using namespace formats::cbddlp;
using namespace formats::config;
using formats::Image;

class FormatCbddlpTest : public ::testing::Test
{
public:
    unsigned char *fileData;
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
        fileData = new unsigned char[size];
        file.read((char *)fileData, size);
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
    ext2_config_t ext2;
    memcpy(&ext2, fileData, sizeof(ext2_config_t));

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

    cout << "level_set_count: " << header.level_set_count << endl
     << "antialias_level: " << ext2.antialias_level << endl
     << "encryption_mode: " << ext2.encryption_mode << endl
     << "mysterious_id: " << ext2.mysterious_id << endl
     << "software_version: " << ext2.software_version << endl
     << "unknown: " << ext2.unknown << endl
    ;

    int layer = 1;
    layer_header_t layderHeaders[header.layer_table_count];
    memcpy(layderHeaders, fileData + header.layer_table_offset, header.layer_table_count * sizeof(layer_header_t));
    unsigned char *imgData = &(fileData[layderHeaders[layer].data_offset]);

    Image image{header.resolution_x, header.resolution_y};
    FormatCbddlp::decode(imgData, layderHeaders[layer].data_len, &image);
    // image.toBitmapImage().save_image("loadedImage.bmp");
    // ASSERT_TRUE(false);
}

TEST_F(FormatCbddlpTest, EncodeDecode)
{

    formats::Image image1{200, 300};

    for (size_t i = 0; i < 200; i++)
    {
        image1.setPixel(i, i, 255);
        image1.setPixel(199 - i, i, 255);
    }
    image1.fill(0, 0, 2, 2, 255);

    unsigned int encodeLength;
    unsigned char *imageBuffer = FormatCbddlp::encode(&image1, encodeLength);

    formats::Image image2{200, 300};
    FormatCbddlp::decode(imageBuffer, encodeLength, &image2);

    for (size_t i = 0; i < 200 * 200; i++)
    {
        ASSERT_EQ(image1.getBitmap()[i], image2.getBitmap()[i])
            << "x: " << i % 200
            << " y: " << i / 200;
    }

    delete[] imageBuffer;
}

TEST_F(FormatCbddlpTest, PackegeTest)
{

    PrinterConfig printerConfig{1440, 2560, 68.04, 120.96, 150};
    ResinConfig resinConfig{150, 100, 10, 150, 150, 1.0, 1.0, 0.5, 90, 0.5, 16, 5, 0.05};

    Image *parts = (Image *)malloc(sizeof(Image) * 20);
    for (size_t i = 0; i < 20; i++)
    {
        parts[i] = Image{printerConfig.getResolutionX(), printerConfig.getResolutionY()};
        parts[i].fill(0, 0, parts[i].getWidth(), 30, 255);
        parts[i].fill(0, parts[i].getHeight() - 30, parts[i].getWidth(), 30, 255);
        parts[i].fill(0, 0, 30, parts[i].getHeight(), 255);
        parts[i].fill(parts[i].getWidth() - 30, 0, 30, parts[i].getHeight(), 255);
        parts[i].fill(0, 0, 100, 100, 255);
    }

    FormatCbddlp formatCbddlp{};

    size_t size;
    const unsigned char *data = formatCbddlp.package(printerConfig, resinConfig, parts, 20, &size);

    // std::ofstream outFile("test.cbddlp");
    // outFile.write((char *)data, size);
    // outFile.flush();
    // outFile.close();

    delete[] data;
    free(parts);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    int ret = RUN_ALL_TESTS();
    return ret;
}