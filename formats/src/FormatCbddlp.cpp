#include <formats/cbddlp/FormatCbddlp.hpp>
#include <formats/RLEEnoce.hpp>
#include <cstring>

using namespace formats::cbddlp;
using namespace formats::config;

void FormatCbddlp::load(char *data, size_t length)
{
    std::memcpy(&header, data, sizeof(cbddlp_file_head_t));
}

inline void generateRGB565(u_short *data, u_char color, u_int &length, u_int &pos)
{
    color >>= 3;
    if (length == 1)
    {
        data[pos++] = (color << 11) | (color << 6) | (0 << 5) | color;
    }
    data[pos++] = (color << 11) | (color << 6) | (1 << 5) | color;
    data[pos++] = 0x300 | length;
}

inline void generateLayer(u_char *data, u_char color, u_int &length, u_int &pos)
{
    data[pos++] = (color > 127) << 7 | length;
}

u_char *FormatCbddlp::encodePreview(Image *src, u_int &length)
{
    return rleEncode<u_short>(src, length, 0xFFF, generateRGB565);
}

u_char *FormatCbddlp::encode(Image *src, u_int &length)
{
    return rleEncode<u_char>(src, length, 0x7F, generateLayer);;
}

void FormatCbddlp::decode(u_char *src, u_int length, Image *dest)
{
    u_int imgPos = 0;
    for (u_int pos = 0; pos < length; pos++)
    {
        u_char value = (src[pos] & 0x80) == 0x80 ? 0xFF : 0x0;
        u_char length = src[pos] & ~0x80;
        for (u_char i = 0; i < length; i++)
        {
            dest->getBitmap()[imgPos++] = value;
        }
    }
}

u_char *FormatCbddlp::package(PrinterConfig &printerConfig, ResinConfig &resinConfig, Image *imageData, const int layers)
{
    cbddlp_file_head_t header;
    header.bed_x_mm = printerConfig.getBedWidth();
    header.bed_y_mm = printerConfig.getBedLength();
    header.bed_y_mm = printerConfig.getBedHeight();
    header.overall_height_mm = layers * resinConfig.getLayerHeight();
    header.layer_height_mm = resinConfig.getLayerHeight();
    header.exposure_s = resinConfig.getLightOnTime();
    header.bot_exposure_s = resinConfig.getBottomLightOnTime();
    header.light_off_time_s = resinConfig.getLightOffTime();
    header.bot_layer_count = resinConfig.getBottomLayerCount();
    header.resolution_x = printerConfig.getResolutionX();
    header.resolution_y = printerConfig.getResolutionY();
    header.print_time_s = layers * 4 +
                          layers * resinConfig.getLightOnTime() +
                          resinConfig.getBottomLayerCount() * (resinConfig.getBottomLightOnTime() - resinConfig.getLightOnTime());

    ext_config_t ext1;
    ext1.bot_lift_dist_mm = resinConfig.getBottomLiftDistance();
    ext1.bot_lift_speed_mmpm = resinConfig.getBottomLiftSpeed();
    ext1.lift_dist_mm = resinConfig.getLiftDistance();
    ext1.lift_speed_mmpm = resinConfig.getLiftSpeed();
    ext1.retract_speed_mmpm = resinConfig.getRetractSpeed();

    ext2_config_t ext2;

    u_int smallImageSize;
    Image smallImage(imageData[layers-1]);
    smallImage.scale(200, 125);
    u_char *smallImage = encodePreview(&smallImage, smallImageSize);
    image_header_t smallImageHeader;
    Image largeImage(imageData[layers-1]);
    smallImage.scale(200, 125);
    u_int largeImageSize;
    u_char *largeImage = encodePreview(&largeImage, largeImageSize);
    image_header_t largeImageHeader;

    u_char *encodedImages[layers];
    u_int encodedSizeTotal;
    layer_header_t layerHeaderTable[layers];
    for (int layer = 0; layer < layers; layer++)
    {
        encodedImages[layer] = encode(&(imageData[layer]), layerHeaderTable->data_len);
        encodedSizeTotal += layerHeaderTable->data_len;
    }

    size_t ext1_pos = sizeof(cbddlp_file_head_t);
    size_t ext2_pos = ext1_pos + sizeof(ext_config_t);
    size_t small_image_header_pos = ext2_pos + sizeof(ext2_config_t);
    size_t large_image_header_pos = small_image_header_pos + sizeof(image_header_t);
    size_t layer_header_table_pos = large_image_header_pos + sizeof(image_header_t);
    size_t small_image_pos = layer_header_table_pos + sizeof(layer_header_t) * layers;
    size_t large_image_pos = small_image_pos + smallImageSize;
    size_t image_table_pos = large_image_pos + largeImageSize;

    header.ext_config_offset = ext1_pos;
    header.ext_config_size = sizeof(ext_config_t);
    header.ext_config2_offset = ext2_pos;
    header.ext_config2_size = sizeof(ext2_config_t);
    header.small_preview_offset = small_image_header_pos;
    header.large_preview_offset = large_image_header_pos;

    size_t size = sizeof(cbddlp_file_head_t) +
                  sizeof(ext_config_t) +
                  sizeof(ext2_config_t) +
                  sizeof(image_header_t) +
                  sizeof(image_header_t) +
                  sizeof(layer_header_t) * layers +
                  smallImageSize +
                  largeImageSize +
                  encodedSizeTotal;

    // package
    u_char *buf = new u_char[size];
    memcpy(buf, &header, sizeof(cbddlp_file_head_t));
    memcpy(buf + ext1_pos, &ext1, sizeof(ext_config_t));
    memcpy(buf + ext2_pos, &ext2, sizeof(ext2_config_t));
    memcpy(buf + small_image_header_pos, &smallImageHeader, sizeof(image_header_t));
    memcpy(buf + large_image_header_pos, &largeImageHeader, sizeof(image_header_t));
    memcpy(buf + layer_header_table_pos, &layerHeaderTable, sizeof(layer_header_t) * layers);
    memcpy(buf + small_image_pos, &smallImage, smallImageSize);
    memcpy(buf + small_image_pos, &largeImage, smallImageSize);
    for (int layer = 0; layer < layers; layer++)
    {
        memcpy(buf + image_table_pos, encodedImages[layer], encodedSizeTotal);
        layerHeaderTable[layers].data_offset = image_table_pos;
        image_table_pos += layerHeaderTable[layers].data_len;
        delete encodedImages[layer];
    }

    return buf;
}