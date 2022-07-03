#include <formats/Image.hpp>
using namespace formats;

Image::Image(const Image &src) : height(src.height), width(src.width)
{
    data = new unsigned char[height * width];
    memcpy(data, src.data, width * height);
}

Image::Image(size_t width, size_t height) : height(height), width(width)
{
    data = new unsigned char[height * width];
    for (size_t i = 0; i < width * height; i++)
    {
        data[i] = 0;
    }
}

Image::~Image()
{
    delete[] data;
}

unsigned char *Image::getBitmap()
{
    return data;
}

void Image::copy(size_t x, size_t y, Image *input)
{
    for (size_t cWidth = 0; cWidth < input->getWidth(); cWidth++)
    {
        for (size_t cHeight = 0; cHeight < input->getHeight(); cHeight++)
        {
            data[(y + cHeight) * width + (x + cWidth)] = input->getPixel(cWidth, cHeight);
        }
    }
}

void Image::fill(size_t x, size_t y, size_t _width, size_t _height, char value)
{
    for (size_t cWidth = 0; cWidth < _width; cWidth++)
    {
        for (size_t cHeight = 0; cHeight < _height; cHeight++)
        {
            data[(y + cHeight) * width + (x + cWidth)] = value;
        }
    }
}

void Image::setPixel(size_t x, size_t y, unsigned char value)
{
    data[y * width + x] = value;
}

unsigned char Image::getPixel(size_t x, size_t y)
{
    return data[y * width + x];
}

bitmap_image Image::toBitmapImage()
{
    bitmap_image bmpImage(width, height);
    for (size_t x = 0; x < width; x++)
    {
        for (size_t y = 0; y < height; y++)
        {
            unsigned char color = getPixel(x, y);
            bmpImage.set_pixel(x, y, color, color, color);
        }
    }
    return bmpImage;
}

size_t Image::getWidth()
{
    return width;
}

size_t Image::getHeight()
{
    return height;
}

void Image::padding(long size)
{
    const size_t length = width * height;
    unsigned char *src = data;
    unsigned char *dest = new unsigned char[length];
    memcpy(dest, src, length);

    for (size_t i = 0; i < abs(size); i++)
    {
        if (size > 0) {
            pad(src, dest, length);
        } else {
            depad(src, dest, length);
        }

        data = dest;
        dest = src;
        src = data;
        memcpy(dest, src, length);
    }

    delete[] dest;
}

void Image::pad(unsigned char *src, unsigned char *dest, size_t length)
{
    for (size_t pos = 0; pos < length; pos++)
    {
        if (dest[pos] != 0)
            continue;
        if ((pos >= width && src[pos - width] != 0) ||
            (pos >= 1 && src[pos - 1] != 0) ||
            (pos + width < length && src[pos + width] != 0) ||
            (pos + 1 < length && src[pos + 1] != 0))
        {
            dest[pos] = 255;
        }
    }
}
void Image::depad(unsigned char *src, unsigned char *dest, size_t length)
{
    for (size_t pos = 0; pos < length; pos++)
    {
        if (dest[pos] == 0)
            continue;
        if ((pos >= width && src[pos - width] == 0) ||
            (pos >= 1 && src[pos - 1] == 0) ||
            (pos + width < length && src[pos + width] == 0) ||
            (pos + 1 < length && src[pos + 1] == 0))
        {
            dest[pos] = 0;
        }
    }
}