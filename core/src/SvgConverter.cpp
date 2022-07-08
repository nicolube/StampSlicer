#include <core/SvgConverter.hpp>
#include <lunasvg.h>

using core::SvgConverter;
using formats::Image;
using formats::config::PrinterConfig;

using namespace lunasvg;

SvgConverter::SvgConverter(formats::config::PrinterConfig &printerConfig, std::string sourcePath)
    : printerConfig(printerConfig),
      svgImage(Document::loadFromFile(sourcePath)),
      width(round(svgImage->width())),
      height(round(svgImage->height()))
{
}

void SvgConverter::setHight(float newHeight)
{
    float px_mmX = printerConfig.getResolutionX() / printerConfig.getBedWidth();
    float px_mmY = printerConfig.getResolutionY() / printerConfig.getBedLength();
    float ratio = (float)width / height;
    width = newHeight * px_mmX;
    height = newHeight * px_mmY;
    std::cout 
    <<"ratio: " <<ratio << std::endl
    <<"width: " <<width << std::endl
    <<"height: " <<height << std::endl
    ;
    if (svgImage->width() > svgImage->height())
        height /= ratio;
    else
        width *= ratio;

    std::cout 
    <<"Oratio: " <<width << std::endl
    <<"Owidth: " <<height << std::endl
    ;
}

Image SvgConverter::toImage()
{
    Bitmap bitmap = svgImage->renderToBitmap(width, height, 0xFFFFFFFF);
    Image image{(int)bitmap.width(), (int)bitmap.height()};

    std::cout 
    <<"Rratio: " <<(int)bitmap.width() << std::endl
    <<"Rwidth: " <<(int)bitmap.height() << std::endl
    ;
    unsigned char *bitmapData = bitmap.data();
    unsigned char *imageData = image.getBitmap();
    for (size_t pos = 0; pos < bitmap.width() * bitmap.height(); pos++)
    {
        imageData[pos] = bitmapData[pos * 4] == 0x00 ? 0xFF : 0;
    }
    return image;
}
