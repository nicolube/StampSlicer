#ifndef INCLUDE_FORMATS_IMAGE_HPP
#define INCLUDE_FORMATS_IMAGE_HPP

#include <stddef.h>
#include <cstring>
#include <bitmap_image.hpp>

namespace formats
{

    class Image
    {
    public:
        explicit Image(const Image &image);
        explicit Image(size_t width, size_t height);
        
        ~Image();

        unsigned char *getBitmap();
        void copy(size_t x, size_t y, Image *input);
        void fill(size_t x, size_t y, size_t width, size_t height, char value);
        void setPixel(size_t x, size_t y, unsigned char value);
        unsigned char getPixel(size_t x, size_t y);
        void padding(long size);
        bitmap_image toBitmapImage();
        size_t getWidth();
        size_t getHeight();

    private:
        unsigned char *data;
        const size_t width;
        const size_t height;
        void pad(unsigned char * src, unsigned char * dest, size_t length);
        void depad(unsigned char * src, unsigned char * dest, size_t length);
    };

};

#endif
