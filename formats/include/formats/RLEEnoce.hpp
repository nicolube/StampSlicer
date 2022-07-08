#ifndef INCLUDE_RLEENOCE_HPP
#define INCLUDE_RLEENOCE_HPP

#include <formats/Image.hpp>

template<typename bufType>
inline unsigned char *rleEncode(formats::Image *src, unsigned int &length, unsigned int limit, void (*genData)(bufType *data, unsigned char color, unsigned int &length, unsigned int &pos)) {
    unsigned char lastValue = 0;
    unsigned int sameCount = 0;
    length = 0;
    const unsigned int imageLength = src->getWidth() * src->getHeight();
    bufType *buf = new bufType[imageLength];
    for (unsigned int pos = 0; pos < imageLength; pos++)
    {
        unsigned char value = src->getBitmap()[pos];
        if (lastValue == value)
        {
            sameCount++;
        }
        else
        {
            if (sameCount > 0)
            {
                (*genData)(buf, lastValue, sameCount, length);
            }
            sameCount = 1;
            lastValue = value;
            continue;
        }
        if (sameCount < limit)
            continue;
        (*genData)(buf, value, sameCount, length);
        sameCount = 0;
    }
    if (sameCount > 0)
        (*genData)(buf, lastValue, sameCount, length);
    length *= sizeof(bufType);
    unsigned char *result = new unsigned char[length ];
    memcpy(result, buf, length);
    delete[] buf;
    return result;
}
#endif