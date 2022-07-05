#include <formats/Image.hpp>
using namespace formats;

Image::Image(const Image &src) : height(src.height), width(src.width)
{
    data = new unsigned char[height * width];
    memcpy(data, src.data, width * height);
}

Image::Image(int width, int height) : height(height), width(width)
{
    data = new unsigned char[height * width];
    fill(0,0, width, height, 0);
}

Image::Image(int width, int height, unsigned char color) : height(height), width(width)
{
    data = new unsigned char[height * width];
    fill(0,0, width, height, color);
}

Image::~Image()
{
    delete[] data;
}

unsigned char *Image::getBitmap()
{
    return data;
}

void Image::copy(int x, int y, Image *input)
{
    for (int cWidth = 0; cWidth < input->getWidth(); cWidth++)
    {
        for (int cHeight = 0; cHeight < input->getHeight(); cHeight++)
        {
            data[(y + cHeight) * width + (x + cWidth)] = input->getPixel(cWidth, cHeight);
        }
    }
}

void Image::fill(int x, int y, int _width, int _height, char value)
{
    for (int cWidth = 0; cWidth < _width; cWidth++)
    {
        for (int cHeight = 0; cHeight < _height; cHeight++)
        {
            data[(y + cHeight) * width + (x + cWidth)] = value;
        }
    }
}

void Image::setPixel(int x, int y, unsigned char value)
{
    data[y * width + x] = value;
}

unsigned char Image::getPixel(int x, int y)
{
    return data[y * width + x];
}

bitmap_image Image::toBitmapImage()
{
    bitmap_image bmpImage(width, height);
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            unsigned char color = getPixel(x, y);
            bmpImage.set_pixel(x, y, color, color, color);
        }
    }
    return bmpImage;
}

int Image::getWidth()
{
    return width;
}

int Image::getHeight()
{
    return height;
}

void Image::padding(long size)
{
    const int length = width * height;
    unsigned char *src = data;
    unsigned char *dest = new unsigned char[length];
    memcpy(dest, src, length);

    for (int i = 0; i < abs(size); i++)
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

void Image::pad(unsigned char *src, unsigned char *dest, int length)
{
    for (int pos = 0; pos < length; pos++)
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
void Image::depad(unsigned char *src, unsigned char *dest, int length)
{
    for (int pos = 0; pos < length; pos++)
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