#ifndef CORE_SVGCONVERTER_HPP
#define CORE_SVGCONVERTER_HPP

#include <string>
#include <formats/Image.hpp>
#include <formats/config/PrinterConfig.hpp>
#include <lunasvg.h>

namespace core
{
    class SvgConverter
    {
    public:
        SvgConverter(formats::config::PrinterConfig &printerConfig, std::string sourcePath);

        void setHight(float height);

        formats::Image toImage();

    private:
        formats::config::PrinterConfig &printerConfig;
        std::unique_ptr<lunasvg::Document> svgImage;
        int width;
        int height;
    };

}

#endif