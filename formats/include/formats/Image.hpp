#ifndef INCLUDE_FORMATS_IMAGE_HPP
#define INCLUDE_FORMATS_IMAGE_HPP

#include <cstring>
#include <bitmap_image.hpp>

namespace formats
{

    class Image
    {
    public:
        Image(const Image &image);
        explicit Image(int width, int height);
        explicit Image(int width, int height, unsigned char color);

        ~Image();

        unsigned char *getBitmap();
        void scale(int width, int heigth);
        void copy(int x, int y, Image *input);
        void fill(int x, int y, int width, int height, char value);
        void setPixel(int x, int y, unsigned char value);
        unsigned char getPixel(int x, int y);
        void padding(int size);
        bitmap_image toBitmapImage();
        int getWidth();
        int getHeight();
        Image &operator=(const Image &src)
        {
            if (this == &src)
                return *this;
            width = src.width;
            height = src.height;
            data = new unsigned char[height * width];
            memcpy(data, src.data, width * height);
            return *this;
        }

    private:
        unsigned char *data;
        int width;
        int height;
        void pad(unsigned char *src, unsigned char *dest, int length);
        void depad(unsigned char *src, unsigned char *dest, int length);
    };

};

#endif
