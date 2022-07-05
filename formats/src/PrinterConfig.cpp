#include <formats/config/PrinterConfig.hpp>

using namespace formats::config;

PrinterConfig::PrinterConfig(int resolutionX, int resolutionY, float bedWidth, float bedLength, float bedHeight)
    : resolutionX(resolutionX), resolutionY(resolutionY), bedWidth(bedWidth), bedLength(bedLength), bedHeight(bedHeight)
{
}

float PrinterConfig::getBedWidth()
{
    return bedWidth;
}

float PrinterConfig::getBedLength()
{
    return bedLength;
}

float PrinterConfig::getBedHeight()
{
    return bedHeight;
}

int PrinterConfig::getResolutionX()
{
    return resolutionX;
}
int PrinterConfig::getResolutionY()
{
    return resolutionY;
}