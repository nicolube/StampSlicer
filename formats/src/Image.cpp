#include <formats/Image.hpp>
using namespace formats;

Image::Image(const Image &src) : height(src.height), width(src.width)
{
    data = new u_char[height * width];
    memcpy(data, src.data, width * height);
}

Image::Image(int width, int height) : height(height), width(width)
{
    data = new u_char[height * width];
    memset(data, 0, height * width);
}

Image::Image(int width, int height, u_char color) : height(height), width(width)
{
    data = new u_char[height * width];
    memset(data, color, height * width);
}

Image::~Image()
{
    delete[] data;
}

u_char *Image::getBitmap()
{
    return data;
}

void Image::scale(int newWidth, int newHeigth)
{
    const size_t size = newWidth * newHeigth;
    u_char *newData = new u_char[size];
    float convX = width / newWidth;
    float convY = height / newHeigth;
    for (size_t x = 0; x < newWidth; x++)
    {
        for (size_t y = 0; y < newHeigth; y++)
        {
            newData[y * newWidth + x] = getPixel(x * convX, y * convY);
        }
    }
    width = newWidth;
    height = newHeigth;
    delete[] data;
    data = newData;
}

void Image::copy(int x, int y, Image *input)
{
    int length = input->getHeight();
    for (int cHeight = 0; cHeight < input->getWidth(); cHeight++)
    {
        memcpy(data + (y + cHeight) * width + x, input->data + cHeight * input->getWidth(), length);
    }
}

void Image::fill(int x, int y, int _width, int _height, char value)
{
    for (int cHeight = 0; cHeight < _height; cHeight++)
    {
        memset(data + (y + cHeight) * width + x, value, _width);
    }
}

void Image::setPixel(int x, int y, u_char value)
{
    data[y * width + x] = value;
}

u_char Image::getPixel(int x, int y)
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
            u_char color = getPixel(x, y);
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
    u_char *src = data;
    u_char *dest = new u_char[length];
    memcpy(dest, src, length);

    for (int i = 0; i < abs(size); i++)
    {
        if (size > 0)
        {
            pad(src, dest, length);
        }
        else
        {
            depad(src, dest, length);
        }

        data = dest;
        dest = src;
        src = data;
        memcpy(dest, src, length);
    }

    delete[] dest;
}

void Image::pad(u_char *src, u_char *dest, int length)
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
void Image::depad(u_char *src, u_char *dest, int length)
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