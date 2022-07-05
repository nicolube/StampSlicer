#include <formats/cbddlp/FormatCbddlp.hpp>
#include <cstring>

using namespace formats::cbddlp;

void FormatCbddlp::load(char *data, size_t length)
{
    std::memcpy(&header, data, sizeof(cbddlp_file_head_t));
}

unsigned char *FormatCbddlp::encode(Image *src, size_t *length)
{
    bool lastValue = false;
    unsigned char sameCount = 0;
    *length = 0;
    const size_t imageLength = src->getWidth() * src->getHeight();
    unsigned char buf[imageLength];
    for (size_t pos = 0; pos < imageLength; pos++)
    {
        bool value = src->getBitmap()[pos] > 127;
        if (lastValue == value)
        {
            sameCount++;
        }
        else
        {
            if (sameCount > 0)
            {
                buf[(*length)++] = lastValue << 7 | sameCount;
            }
            sameCount = 1;
            lastValue = value;
            continue;
        }
        if (sameCount < 0x80 - 1)
            continue;
        buf[(*length)++] = value << 7 | sameCount;
        sameCount = 0;
    }
    if (sameCount > 0)
        buf[(*length)++] = lastValue << 7 | sameCount;

    unsigned char *result = new unsigned char[*length];
    memcpy(result, buf, *length);
    return result;
}

void FormatCbddlp::decode(unsigned char *src, size_t length, Image *dest)
{
    size_t imgPos = 0;
    for (size_t pos = 0; pos < length; pos++)
    {
        unsigned char value = (src[pos] & 0x80) == 0x80 ? 0xFF : 0x0;
        unsigned char length = src[pos] & ~0x80;
        for (unsigned char i = 0; i < length; i++)
        {
            dest->getBitmap()[imgPos++] = value;
        }
    }
}