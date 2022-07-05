#ifndef INCLUDE_RLEENOCE_HPP
#define INCLUDE_RLEENOCE_HPP

#include <formats/Image.hpp>

template<typename bufType>
inline u_char *rleEncode(formats::Image *src, u_int &length, u_int limit, void (*genData)(bufType *data, u_char color, u_int &length, u_int &pos)) {
    u_char lastValue = 0;
    u_int sameCount = 0;
    length = 0;
    const u_int imageLength = src->getWidth() * src->getHeight();
    bufType buf[imageLength];
    for (u_int pos = 0; pos < imageLength; pos++)
    {
        u_char value = src->getBitmap()[pos];
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

    u_char *result = new u_char[length];
    memcpy(result, buf, length);
    return result;
}
#endif