#include <core/SvgConverter.hpp>
#include <lunasvg.h>

using core::SvgConverter;
using formats::Image;
using formats::config::PrinterConfig;

using namespace lunasvg;

SvgConverter::SvgConverter(formats::config::PrinterConfig &printerConfig, std::string sourcePath)
    : printerConfig(printerConfig),
      svgImage(Document::loadFromFile(sourcePath))
{
}

void SvgConverter::setHight(float height)
{

}

Image SvgConverter::toImage()
{
    float px_mm = printerConfig.getResolutionX() / printerConfig.getBedWidth();
    int width =  60 * px_mm;
    int height = (60 * px_mm) * (svgImage->width() / svgImage->height());
    Bitmap bitmap = svgImage->renderToBitmap(width, height, 0xFFFFFFFF);
    Image image{bitmap.width(), bitmap.height()};
    u_char *bitmapData = bitmap.data();
    u_char *imageData = image.getBitmap();
    for (size_t pos = 0; pos < bitmap.width() * bitmap.height(); pos++)
    {
            imageData[pos] = bitmapData[pos * 4] == 0x00 ? 0xFF : 0;
    }
    image.toBitmapImage().save_image("test.bmp");
    
    return image;
}
