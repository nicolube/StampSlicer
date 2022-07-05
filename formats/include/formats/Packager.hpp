#ifndef INCLUDE_FORMATS_PACKAGER_HPP
#define INCLUDE_FORMATS_PACKAGER_HPP

#include <formats/Image.hpp>
#include <formats/config/PrinterConfig.hpp>
#include <formats/config/ResinConfig.hpp>

namespace formats
{
    class Packager
    {
    public:
        Packager() = default;
        virtual ~Packager() = default;
        virtual u_char *package(formats::config::PrinterConfig &printerConfig, formats::config::ResinConfig &resinConfig, Image *imageData, const int layers, size_t * size) = 0;
    };
    
}

#endif