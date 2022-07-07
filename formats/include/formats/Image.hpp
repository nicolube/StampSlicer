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
        Image(const Image &image);
        explicit Image(int width, int height);
        explicit Image(int width, int height, u_char color);

        ~Image();

        u_char *getBitmap();
        void scale(int width, int heigth);
        void copy(int x, int y, Image *input);
        void fill(int x, int y, int width, int height, char value);
        void setPixel(int x, int y, u_char value);
        u_char getPixel(int x, int y);
        void padding(long size);
        bitmap_image toBitmapImage();
        int getWidth();
        int getHeight();
        Image &operator=(const Image &src)
        {
            if (this == &src)
                return *this;
            width = src.width;
            height = src.height;
            data = new u_char[height * width];
            memcpy(data, src.data, width * height);
            return *this;
        }

    private:
        u_char *data;
        int width;
        int height;
        void pad(u_char *src, u_char *dest, int length);
        void depad(u_char *src, u_char *dest, int length);
    };

};

#endif
